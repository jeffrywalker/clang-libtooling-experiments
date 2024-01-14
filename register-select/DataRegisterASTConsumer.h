#pragma once

#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"

#include "DataRegisterVisitor.h"

namespace data_registration
{

    class DataRegisterASTConsumer : public clang::ASTConsumer
    {
            public:
        // override the constructor in order to pass CI
        explicit DataRegisterASTConsumer(clang::CompilerInstance* ci);

        // override this to call our ExampleVisitor on the entire source file
        virtual void HandleTranslationUnit(clang::ASTContext& context);

            private:
        std::unique_ptr<DataRegisterVisitor> visitor;
    };
}  // namespace data_registration