#include "ClassField.h"
#include "Context.h"
#include "DataRegisterUtils.h"
#include "Logger.h"
#include "Writer.h"

#include "clang/AST/Decl.h"
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
    m_context                      = &context;
    const RegisterRequest* request = Config::get().getRequest(classItem);
    std::string node               = "ERROR";
    if (request != nullptr)
    {
        node = request->node;
    }
    registerFieldDecl(node, m_F);
}

void ClassField::registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd,
                                   const data_registration::RegisteredVariable* parent /*= nullptr*/)
{
    const clang::RecordDecl* rd         = fd->getParent();
    const clang::QualType qt            = fd->getType();
    const clang::Type* t                = qt.getTypePtr();
    const clang::RecordDecl* typeRecord = t->getAsRecordDecl();

    // register entry for this field
    data_registration::RegisteredVariable regVar;
    regVar.update(fd, listName, parent);

    if (m_context != nullptr)
        m_context->registerEnum(regVar.enumName, regVar.getEnumRegistrationCode());

    if (regVar.isBuiltIn || regVar.isEnum)
    {
        // simplest scenario where array doesn't require additional handling
        Writer::get().bufferRegister(regVar.getRegistrationCode());
    }
    else if (regVar.isStruct || regVar.isClass)
    {
        registerStructClass(listName, fd, &regVar, regVar.isArray);
        /*
        /// MIGRATED
        Writer::get().bufferRegister(regVar.getRegistrationCode());

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
                    ss << " is public";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_protected)
                {
                    ss << " is protected";
                    canRegisterBase = true;
                }
                else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_private)
                {
                    ss << " is private";
                    /// TODO would require check for public/protected register method
                }
                Logger::get().debug(ss.str());
                if (canRegisterBase)
                {
                    // template base class
                    walkTemplateBase(baseType, &regVar, listName);

                    // apply filter to base classes that are not templates as the fields will be read directly
                    std::string classBaseName = regVar.className + "::" + baseName;
                    if (!Config::get().doRegisterImplicitClassField(classBaseName))
                    {
                        Logger::get().debug("Excluding filtered class base: " + classBaseName);
                        continue;
                    }
                    // fields of the base class
                    for (const auto* childField : baseType->fields())
                    {
                        registerFieldDecl(listName, childField, &regVar);
                    }
                }
            }
        }

        // traverse the children
        std::string _type_str = "(unk)";
        if (t->isStructureType())
        {
            _type_str = "(struct)";
        }
        else if (t->isClassType())
        {
            _type_str = "(class)";
        }
        Logger::get().debug("Adding child fields for " + _type_str + " " + regVar.typeName);
        for (const auto* childField : typeRecord->fields())
        {
            if (regVar.isClass)
            {
                std::string classFieldName = regVar.className + "::" + childField->getName().str();
                if (!Config::get().doRegisterImplicitClassField(classFieldName))
                {
                    Logger::get().debug("Excluding filtered class field: " + classFieldName);
                    continue;
                }
            }
            registerFieldDecl(listName, childField, &regVar);
        }
        */
    }
    else
    {
        Logger::get().error("Unexpected conditional encountered!");
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
            /// FIXME needs to be instance class name
            std::string qualName = parent->typeName + "::" + ctsdBaseType->getNameAsString();
            Logger::get().debug("CTSD BASE: " + qualName);
            /// TODO apply class filters to the template base (require instance not template class name)
            for (const auto* baseField : ctsdBaseType->fields())
            {
                registerFieldDecl(listName, baseField, parent);
            }
        }
    }
}

void ClassField::registerStructClass(const std::string& listName, const clang::FieldDecl* fd, const RegisteredVariable* parent,
                                     bool isArray)
{
    Writer::get().bufferRegister(parent->getRegistrationCode());

    const clang::QualType qt            = fd->getType();
    const clang::Type* t                = qt.getTypePtr();
    const clang::RecordDecl* typeRecord = t->getAsRecordDecl();

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
                ss << " is public";
                canRegisterBase = true;
            }
            else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_protected)
            {
                ss << " is protected";
                canRegisterBase = true;
            }
            else if (itr.getAccessSpecifierAsWritten() == clang::AccessSpecifier::AS_private)
            {
                ss << " is private";
                /// TODO would require check for public/protected register method
            }
            Logger::get().debug(ss.str());
            if (canRegisterBase)
            {
                // template base class
                walkTemplateBase(baseType, parent, listName);

                // apply filter to base classes that are not templates as the fields will be read directly
                std::string classBaseName = parent->className + "::" + baseName;
                if (!Config::get().doRegisterImplicitClassField(classBaseName))
                {
                    Logger::get().debug("Excluding filtered class base: " + classBaseName);
                    continue;
                }
                // fields of the base class
                for (const auto* childField : baseType->fields())
                {
                    registerFieldDecl(listName, childField, parent);
                }
            }
        }
    }

    // traverse the children
    std::string _type_str = "(unk)";
    if (t->isStructureType())
    {
        _type_str = "(struct)";
    }
    else if (t->isClassType())
    {
        _type_str = "(class)";
    }
    Logger::get().debug("Adding child fields for " + _type_str + " " + parent->typeName);
    for (const auto* childField : typeRecord->fields())
    {
        if (parent->isClass)
        {
            std::string classFieldName = parent->className + "::" + childField->getName().str();
            if (!Config::get().doRegisterImplicitClassField(classFieldName))
            {
                Logger::get().debug("Excluding filtered class field: " + classFieldName);
                continue;
            }
        }
        registerFieldDecl(listName, childField, parent);
    }
}