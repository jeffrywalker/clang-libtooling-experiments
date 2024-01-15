#include "ClassField.h"
#include "Context.h"
#include "DataRegisterUtils.h"
#include "Logger.h"
#include "Writer.h"

#include "clang/AST/DeclCXX.h"
#include "clang/AST/RecursiveASTVisitor.h"

using namespace data_registration;
using namespace clang;

ClassField::ClassField(const clang::FieldDecl* F) : m_F(F)
{
}

std::string ClassField::id() const
{
    return m_F->getQualifiedNameAsString();
}

void ClassField::generateRegistration(Context& context, const std::string& classItem)
{
    const RegisterRequest* request = Config::get().getRequest(classItem);
    std::string node               = "ERROR";
    if (request != nullptr)
    {
        node = request->node;
    }
    // registerFieldDecl(request.node, m_F);
    registerFieldDecl(node, m_F);
}

/// TODO needs to be part of class for the recursive handling
/// TODO need to support derived classes
/// TODO need "binder" equivalent class that checks for ability to register. For example, protected/private base classes.
void ClassField::registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd,
                                   const data_registration::RegisteredVariable* parent /*= nullptr*/)
{
    const clang::RecordDecl* rd         = fd->getParent();
    const clang::QualType qt            = fd->getType();
    const clang::Type* t                = qt.getTypePtr();
    const clang::RecordDecl* typeRecord = t->getAsRecordDecl();
    bool isBuiltIn                      = t->isBuiltinType();
    /// TODO this is probably better than the 'isCompoundType' below
    bool isClassOrStruct = t->isStructureType() || t->isClassType();
    bool isCompoundType  = !t->isBuiltinType() && !t->isEnumeralType();

    ASTContext& context = fd->getASTContext();
    // register entry for this field
    data_registration::RegisteredVariable regVar;
    regVar.listName = listName;
    regVar.setName(fd->getName().str());
    if (parent != nullptr)
    {
        regVar.setParent(parent);
    }

    if (isBuiltIn)
    {
        if (const clang::BuiltinType* bit = t->getAs<clang::BuiltinType>())
        {
            clang::PrintingPolicy pp(context.getLangOpts());
            regVar.typeName = bit->getName(pp).str();
        }
    }
    else if (t->isEnumeralType())
    {
        if (const clang::EnumType* et = t->getAs<clang::EnumType>())
        {
            regVar.enumName = et->getAsTagDecl()->getNameAsString();
            // add enumerated values as convention to demonstrate reading enum
            /// FIXME correct registration code
            std::string enumConvention      = "";
            const clang::EnumDecl* enumDecl = et->getDecl();
            std::stringstream ss;
            ss << "{\nstd::vector<std::pair<std::wstring, int>> entryList = \n{\n";
            for (auto it = enumDecl->enumerator_begin(); it != enumDecl->enumerator_end(); it++)
            {
                enumConvention += it->getNameAsString() + "(" + std::to_string(it->getInitVal().getSExtValue()) + ") ";
                ss << "  {L\"" << it->getNameAsString() << "\", " << std::to_string(it->getInitVal().getSExtValue()) << "},\n";
            }
            ss << "}; // " << regVar.enumName << "\n}\n";
            Writer::get().bufferEnum(ss.str());
            regVar.convention = enumConvention;
        }
    }
    else
    {
        regVar.typeName = typeRecord->getNameAsString();
    }

    if (auto comment = context.getLocalCommentForDeclUncached(fd))
    {
        readComments(comment, context, regVar);
    }
    if (regVar.units == data_registration::INHERIT_UNIT && parent != nullptr)
    {
        regVar.units = parent->units;
    }

    if (isCompoundType)
    {
        Writer::get().bufferRegister(regVar.dumpStr());

        // check for base classes
        const clang::CXXRecordDecl* tcxx = t->getAsCXXRecordDecl();
        if (tcxx->getNumBases() > 0)
        {
            for (const auto itr : tcxx->bases())
            {
                const clang::RecordDecl* baseType = itr.getType().getTypePtr()->getAsRecordDecl();
                std::string baseName              = baseType->getNameAsString();
                std::stringstream ss;
                ss << "base: " << baseName;
                bool canRegisterBase = false;
                if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_public)
                {
                    ss << " is public\n";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_protected)
                {
                    ss << " is protected\n";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_private)
                {
                    ss << " is private\n";
                    /// TODO would require check for public/protected register method
                }
                Logger::get().debug(ss.str());
                if (canRegisterBase)
                {
                    // template base class
                    walkTemplateBase(baseType, &regVar, listName);

                    // fields of the base class
                    for (const auto* childField : baseType->fields())
                    {
                        registerFieldDecl(listName, childField, &regVar);
                    }
                }
            }
        }

        // traverse the children
        for (const auto* childField : typeRecord->fields())
        {
            registerFieldDecl(listName, childField, &regVar);
        }
    }
    else
    {
        regVar.isBasicType = true;
        Writer::get().bufferRegister(regVar.dumpStr());
    }
}

void ClassField::walkTemplateBase(const clang::RecordDecl* baseType, const RegisteredVariable* parent, const std::string& listName)
{
    if (const auto* CTSD = dyn_cast<clang::ClassTemplateSpecializationDecl>(baseType))
    {
        for (const auto b : CTSD->bases())
        {
            const auto* btp = b.getType().getTypePtrOrNull();
            if (btp == nullptr)
                continue;

            const clang::RecordDecl* ctsdBaseType = btp->getAsRecordDecl();
            /// HACK check if this is to be registered
            /// FIXME needs to be instance class name
            std::string qualName = parent->typeName + "::" + ctsdBaseType->getNameAsString();
            Logger::get().debug("CTSD BASE: " + qualName);
            // FIXME FILTER CHECK if (cfg.doRegister_classField(qualName))
            // FIXME FILTER CHECK {
            for (const auto* baseField : ctsdBaseType->fields())
            {
                // spDataRegister p = std::make_shared<ClassField>(baseField);
                // m_context.add(p, qualName);
                registerFieldDecl(listName, baseField, parent);
            }
            // }
        }
    }
}