#pragma once

#include "DataRegister.h"
#include "RegisteredVariable.h"

namespace clang
{
    class FieldDecl;
    class RecordDecl;
}  // namespace clang

namespace data_registration
{
    /// represents a class field (i.e., class member) that is to be registered
    class ClassField : public DataRegister
    {
            public:
        ClassField(const clang::FieldDecl* F);

        std::string id() const override;

        void generateRegistration(Context& context, const std::string& classItem) override;

            private:
        const clang::FieldDecl* m_F;
        Context* m_context = nullptr;

        /// processes a field declaration traversing children if not a built-in type
        /// \param [in] list name this is being registered as
        /// \param [in] fd the field being processed
        /// \param [in] parent used by recursive calls when (field) is a compound type
        void registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd, const RegisteredVariable* parent = nullptr);

        void registerStructClass(const std::string& listName, const clang::FieldDecl* fd, const RegisteredVariable* parent,
                                 bool isArray);

        /// walks the template base class
        void walkTemplateBase(const clang::RecordDecl* baseType, const RegisteredVariable* parent, const std::string& listName);
    };
}  // namespace data_registration