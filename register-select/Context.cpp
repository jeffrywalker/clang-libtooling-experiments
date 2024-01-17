#include "Context.h"
#include "Logger.h"
#include "Writer.h"
#include "str_utils.h"

using namespace data_registration;
using namespace str_utils;

Context::Context()
{
    m_ids.clear();
    m_enumIds.clear();
}

// TODO need the generate list code (should return pointer for this action)
// TODO cmake pass includes
// TODO filters for ignoring certain includes? (speed up build)
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
    /// TODO needs user config hooks for output code (and removal of this temp prefix)
    std::stringstream tempPrefixCode;
    tempPrefixCode
        << "#include <string>\n"
        << "#include <chrono>\n"
        << "#include <vector>\n"
        << "#include <utility>\n\n"
        << "// REMOVE ME\n"
        << "class IVarDef {\npublic:\n"
        << tab() << "enum vartype { ENUM };\n"
        << tab() << "template <typename T> static vartype getVarType(T var){}\n"
        << "};\n"
        << "// REMOVE ME\n"
        << "class IVarList {\npublic:\n"
        << tab()
        << "void addReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* "
           "units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName)\n"
        << tab() << "{}\n"
        << tab()
        << "void addVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, "
           "const wchar_t* defaultValue, const wchar_t* range, IVarDef::vartype varType, void* address, const wchar_t* enumName = "
           "nullptr)\n"
        << tab() << "{}\n"
        << tab() << "bool checkForChange(const wchar_t*){}\n"
        << tab() << "void alignToList(IVarList*){}\n"
        << tab() << "IVarList* createComparisonList(){}\n"
        << "};\n"
        << "// REMOVE ME\n"
        << "class IVarData {\npublic:\n"
        << tab() << "IVarList* getList(const wchar_t* name){}\n"
        << tab() << "IVarList* createVarList(const wchar_t* name, unsigned int* r=(unsigned int*)nullptr){}\n"
        << "};\n"
        << "\n\n";

    std::stringstream ss;
    ss << tempPrefixCode.str()  //
       << "bool " << config.rootClassName << "::registerData(const std::wstring& listName, IVarData* pVarData)\n{\n"
       << tab() << "// create an always unique hash (temporary)\n"
       << tab()
       << "std::wstring hack_changingHash = listName + "
          "std::to_wstring(std::chrono::steady_clock().now().time_since_epoch().count());\n"
       << tab() << "IVarList* pvl = pVarData->getList(listName.c_str());\n"
       << tab() << "IVarList* pvl_old = pvl;\n"
       << tab() << "bool doAlign = false;\n"
       << tab() << "if (pvl != nullptr)\n"
       << tab() << "{\n"
       << tab(2) << "if (pvl->checkForChange(hack_changingHash.c_str()))\n"
       << tab(2) << "{\n"
       << tab(3) << "pvl = pvl->createComparisonList();\n"
       << tab(3) << "doAlign = true;\n"
       << tab(2) << "}\n"
       << tab() << "}\n"
       << tab() << "if (pvl == nullptr)\n"
       << tab() << "{\n"
       << tab(2) << "pvl = pVarData->createVarList(listName.c_str());\n"
       << tab(2) << "if (pvl == nullptr)\n"
       << tab(3) << "return false;\n"
       << tab(2) << "pvl->checkForChange(hack_changingHash.c_str());\n"
       << tab() << "}\n\n";
    Writer::get().write(ss.str());

    for (auto itr : m_rootRegisters)
    {
        itr.first->generateRegistration(*this, itr.second);
    }
    Writer::get().writeEnum();
    Writer::get().writeRegister();
    // closing code
    ss.str("");
    ss << tab() << "if (doAlign)\n"
       << tab(2) << "pvl_old->alignToList(pvl);\n"
       << tab() << "// pVarList = pvl;\n"
       << tab() << "return true;\n"
       << "}";
    Writer::get().write(ss.str());
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
    m_ids.insert(dataRegister->id());
}

void Context::registerEnum(const std::string& enumName, const std::string& enumCode)
{
    if (enumName.empty() || m_enumIds.count(enumName))
    {
        return;
    }
    m_enumIds.insert(enumName);
    Logger::get().info("Adding ENUM: " + enumName);

    Writer::get().bufferEnum(enumCode);
}