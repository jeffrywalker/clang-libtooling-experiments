#include "DataRegisterFrontendAction.h"
#include "DataRegisterASTConsumer.h"

using namespace data_registration;
using namespace clang;
using namespace llvm;

std::unique_ptr<clang::ASTConsumer> DataRegisterFrontendAction::CreateASTConsumer(CompilerInstance& ci, StringRef file)
{
    outs() << "Process input file " << file << "\n";
    return std::unique_ptr<ASTConsumer>(new DataRegisterASTConsumer(&ci));
}