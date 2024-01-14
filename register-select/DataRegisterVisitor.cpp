#include "DataRegisterVisitor.h"
#include "Config.h"
#include "Options.h"

#include "ClassField.h"
#include "DataRegisterUtils.h"
#include "Logger.h"

#include <iostream>

using namespace data_registration;
using namespace clang;

DataRegisterVisitor::DataRegisterVisitor(CompilerInstance* ci) : ast_context(&(ci->getASTContext()))
{
    Config& config = Config::get();
    Logger& logger = Logger::get();

    /// TODO all options
    if (O_log_level == "DEBUG")
    {
        logger.setLogLevel(Logger::LogLevel::DEBUG);
    }
    config.outputFileName = O_output_file;

    config.outputDir     = O_output_dir;
    config.outputInclude = O_output_include;

    if (O_config.size())
        config.read(O_config);
    if (O_suppress_errors)
    {
        clang::DiagnosticsEngine& di = ci->getDiagnostics();
        di.setSuppressAllDiagnostics(true);
    }
}
DataRegisterVisitor::~DataRegisterVisitor()
{
}

bool DataRegisterVisitor::shouldVisitTemplateInstantiations() const
{
    return true;
}

bool DataRegisterVisitor::VisitFunctionDecl(clang::FunctionDecl* F)
{
    if (F->isCXXInstanceMember() || isa<CXXMethodDecl>(F))
        return true;

    Logger::get().debug("VisitFunctionDecl: " + F->getQualifiedNameAsString());

    return true;
}

bool DataRegisterVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl* C)
{
    // if (C->isCXXInstanceMember() || C->isCXXClassMember())
    //     return true;

    std::string className = C->getQualifiedNameAsString();
    Logger::get().debug("VisitCXXRecordDecl: " + className);
    /// TODO need to check if this class is to be registered
    /// ... config needs to be split up by classes
    /// HACK for test
    /*
    bool isRegisteredClass = false;
    for (const auto r : Config::get().getRegisters())
    {
        if (r.second.starts_with(className))
        {
            isRegisteredClass = true;
            break;
        }
    }
    if (!isRegisteredClass)
    {
        return true;
    }

    C->dumpColor();
    Logger::get().debug("NumBases " + std::to_string(C->getNumBases()));
    for (const auto base : C->bases())
    {
        const clang::Type* baseTypePtr = base.getType().getTypePtrOrNull();
        if (baseTypePtr == nullptr)
        {
            continue;
        }
        const clang::CXXRecordDecl* baseType = baseTypePtr->getAsCXXRecordDecl();
        if (baseType != nullptr)
        {
            std::string prefix = "BaseRecord";
            if (const auto* CTSD = dyn_cast<clang::ClassTemplateSpecializationDecl>(baseType))
            {
                prefix += "(CTSD)";
                Logger::get().debug(prefix + " " + baseType->getNameAsString());
                // CTSD->dumpColor();

                for (const auto b : CTSD->bases())
                {
                    const auto* btp = b.getType().getTypePtrOrNull();
                    if (btp == nullptr)
                        continue;

                    const clang::RecordDecl* baseType = btp->getAsRecordDecl();
                    Logger::get().debug(baseType->getNameAsString());
                    /// HACK check if this is to be registered
                    std::string qualName = className + "::" + baseType->getNameAsString();
                    auto rtn             = Config::get().doRegister_classMember(qualName);
                    if (rtn.first)
                    {
                        for (const auto* baseField : baseType->fields())
                        {
                            registerFieldDecl(rtn.second, baseField);
                        }
                    }
                }
            }
        }
    }
    */
    // if (binder::is_bindable(C))
    // {
    //     binder::BinderOP b = std::make_shared<binder::ClassBinder>(C);
    //     context.add(b);
    // }

    return true;
}

bool DataRegisterVisitor::VisitFieldDecl(clang::FieldDecl* F)
{
    std::string qualName = F->getQualifiedNameAsString();
    /// TODO: fields are class members, this would be what is spec'd in the config file for the simple case
    /// HACK for test
    Config& cfg = Config::get();
    if (cfg.doRegister_classField(qualName))
    {
        spDataRegister p = std::make_shared<ClassField>(F);
        m_context.add(p, qualName);
    }

    return true;
}

bool DataRegisterVisitor::VisitEnumDecl(clang::EnumDecl* E)
{
    if (E->isCXXInstanceMember() || E->isCXXClassMember())
        return true;

    Logger::get().debug("VisitEnumDecl: " + E->getQualifiedNameAsString());

    return true;
}

void DataRegisterVisitor::generate()
{
    m_context.generate(Config::get());
}