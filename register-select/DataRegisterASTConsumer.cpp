#include "DataRegisterASTConsumer.h"

using namespace data_registration;
using namespace clang;


DataRegisterASTConsumer::DataRegisterASTConsumer(clang::CompilerInstance* ci) : visitor(new DataRegisterVisitor(ci))
{
}

void DataRegisterASTConsumer::HandleTranslationUnit(ASTContext& context)
{
    visitor->TraverseDecl(context.getTranslationUnitDecl());
    visitor->generate();
}