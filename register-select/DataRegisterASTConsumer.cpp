#include "DataRegisterASTConsumer.h"
#include "Logger.h"

using namespace data_registration;
using namespace clang;


DataRegisterASTConsumer::DataRegisterASTConsumer(clang::CompilerInstance* ci) : visitor(new DataRegisterVisitor(ci))
{
}

void DataRegisterASTConsumer::HandleTranslationUnit(ASTContext& context)
{
    Logger::get().debug("Reading AST");
    visitor->TraverseDecl(context.getTranslationUnitDecl());
    Logger::get().debug("Requesting registration generation");
    visitor->generate();
}