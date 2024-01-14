#pragma once

#include "clang/AST/Decl.h"

#include "DataRegister.h"
#include "RegisteredVariable.h"

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
        void registerFieldDecl(const std::string& listName, const clang::FieldDecl* fd,
                               const data_registration::RegisteredVariable* parent = nullptr);
    };
}  // namespace data_registration