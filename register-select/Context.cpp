#include "Context.h"
#include "Logger.h"
#include "Writer.h"

using namespace data_registration;

Context::Context()
{
    m_ids.clear();
}

void Context::generate(const Config& config)
{
    std::string out_file = config.outputFileName;
    if (!config.outputDir.empty())
    {
        out_file = config.outputDir + "/" + config.outputFileName;
    }
    Writer::get().openFile(out_file);
    if (!config.outputInclude.empty())
    {
        Writer::get().write("#include \"" + config.outputInclude + "\"\n");
    }
    /// HACK needs user config
    std::stringstream ss;
    ss << "#include <string>\n";
    ss << "#include <vector>\n"
       << "#include <utility>\n";
    ss << "void registerReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* "
          "units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName){}\n";
    ss << "void registerVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, "
          "const wchar_t* defaultValue, const wchar_t* range, const wchar_t* varType, void* address, const wchar_t* enumName = "
          "nullptr){}\n";
    ss << "void " << config.rootClassName << "::registerData()\n{\n";
    Writer::get().write(ss.str());

    for (auto itr : m_rootRegisters)
    {
        itr.first->generateRegistration(*this, itr.second);
    }
    /// HACK
    Writer::get().writeEnum();
    Writer::get().writeRegister();
    Writer::get().write("\n}");
    Writer::get().close();

    // check that all requests were made
    for (const auto rqst : Config::get().getRegisters())
    {
        if (!rqst.isMatched)
        {
            Logger::get().warn("NOT REGISTERED: " + rqst.classItem);
        }
    }
}

void Context::add(spDataRegister& dataRegister, const std::string& classItem)
{
    Logger::get().debug("adding: " + dataRegister->id());
    if (m_ids.count(dataRegister->id()))
    {
        Logger::get().warn("Duplicate ID requested for: " + dataRegister->id());
        return;
    }
    Logger::get().info("Adding ID: " + dataRegister->id());

    m_rootRegisters.push_back(std::make_pair(dataRegister, classItem));
    // m_rootRegisters.push_back(dataRegister);
    m_ids.insert(dataRegister->id());
}