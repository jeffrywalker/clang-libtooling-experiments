#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"

#include "Config.h"
#include "Context.h"
#include "DataRegister.h"

namespace data_registration
{
    class DataRegisterVisitor : public clang::RecursiveASTVisitor<DataRegisterVisitor>
    {
            public:
        explicit DataRegisterVisitor(clang::CompilerInstance* ci);
        virtual ~DataRegisterVisitor();

        bool shouldVisitTemplateInstantiations() const;

        /// visits all functions
        virtual bool VisitFunctionDecl(clang::FunctionDecl* F);
        /// visits all classes
        virtual bool VisitCXXRecordDecl(clang::CXXRecordDecl* C);
        /// visits all enumerations
        virtual bool VisitEnumDecl(clang::EnumDecl* E);
        /// visits all fields (structure and class members)
        virtual bool VisitFieldDecl(clang::FieldDecl* F);

        void generate(void);

            private:
        clang::ASTContext* ast_context;

        /// root output writer
        data_registration::Context m_context;
    };
}  // namespace data_registration