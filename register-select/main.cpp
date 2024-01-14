// Declares clang::SyntaxOnlyAction.
// #include "clang/AST/ASTDumper.h"
// #include "clang/AST/Comment.h"
// #include "clang/AST/CommentVisitor.h"
// #include "clang/AST/RawCommentList.h"
// #include "clang/ASTMatchers/ASTMatchFinder.h"
// #include "clang/ASTMatchers/ASTMatchers.h"
// #include "clang/Frontend/FrontendActions.h"

#include "DataRegisterFrontendAction.h"
#include "Options.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

#include <iostream>

using namespace clang::tooling;
using namespace llvm;
using namespace clang;
using namespace data_registration;

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

int main(int argc, const char** argv)
{
    if (llvm::Expected<CommonOptionsParser> eop = CommonOptionsParser::create(argc, argv, DataRegisterToolCategory))
    {
        ClangTool tool(eop->getCompilations(), eop->getSourcePathList());
        return tool.run(newFrontendActionFactory<DataRegisterFrontendAction>().get());
    }
    else
    {
        auto errs = eop.takeError();
        llvm::logAllUnhandledErrors(std::move(errs), outs(), "\nErrors:\n");
        return 1;
    }
}