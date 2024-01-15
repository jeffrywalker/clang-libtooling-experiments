#include "ClassStruct.h"
#include "ClassField.h"
#include "Logger.h"

#include "clang/AST/DeclCXX.h"
#include "clang/AST/RecursiveASTVisitor.h"

using namespace data_registration;
using namespace clang;

ClassStruct::ClassStruct(const clang::CXXRecordDecl* C) : m_C(C)
{
}

std::string ClassStruct::id() const
{
    return m_C->getQualifiedNameAsString();
}

void ClassStruct::generateRegistration(Context& context, const std::string& classItem)
{
    const RegisterRequest* request = Config::get().getRequest(classItem);
    std::string node               = "ERROR";
    if (request != nullptr)
    {
        node = request->node;
    }
    Logger::get().debug("Registering " + classItem);
    for (const auto& field : m_C->fields())
    {
        ClassField classField(field);
        classField.generateRegistration(context, classItem);
    }
}