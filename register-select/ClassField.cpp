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
    bool isClassOrStruct                = t->isStructureType() || t->isClassType();  /// NOTE: probably better than 'isCompoundType'
    bool isCompoundType                 = !t->isBuiltinType() && !t->isEnumeralType();

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
            std::string enumConvention      = "";
            const clang::EnumDecl* enumDecl = et->getDecl();
            for (auto it = enumDecl->enumerator_begin(); it != enumDecl->enumerator_end(); it++)
            {
                enumConvention += it->getNameAsString() + "(" + std::to_string(it->getInitVal().getSExtValue()) + ") ";
            }
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
        Writer::get().write(regVar.dumpStr());

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
        Writer::get().write(regVar.dumpStr());
    }
}