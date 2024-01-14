#pragma once

#include "clang/Frontend/FrontendActions.h"

namespace data_registration
{
    /// entrypoint frontend used by the tool
    class DataRegisterFrontendAction : public clang::ASTFrontendAction
    {
            public:
        virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& ci, llvm::StringRef file);
    };
}  // namespace data_registration