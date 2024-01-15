#pragma once

#include "clang/AST/Decl.h"

#include "DataRegister.h"
#include "RegisteredVariable.h"

namespace data_registration
{
    /// represents a class or struct
    class ClassStruct : public DataRegister
    {
            public:
        ClassStruct(const clang::CXXRecordDecl* C);

        std::string id() const override;

        void generateRegistration(Context& context, const std::string& classItem) override;

            private:
        const clang::CXXRecordDecl* m_C;

        Context* m_context = nullptr;
    };
}  // namespace data_registration