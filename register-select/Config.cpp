#include "Config.h"
#include "Logger.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <iostream>

using namespace data_registration;

enum class InitBlock
{
    SETUP = 0,
    CLASSES,
    LISTS
};

Config::Config()
{
}

Config& Config::get()
{
    static Config* instance = nullptr;
    if (!instance)
    {
        instance = new Config();
    }
    return *instance;
}

void Config::read(const std::string& file_name)
{
    // keywords used in the config file
    const std::string LIST_TOKEN = "list";
    InitBlock initBlock          = InitBlock::SETUP;

    std::ifstream f(file_name);
    if (!f.good())
    {
        throw std::runtime_error("can not open file " + file_name + " for reading...");
    }
    std::string line;
    // read the file line by line
    while (std::getline(f, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        if (line.back() == '\r')
        {
            line.pop_back();
            if (line.empty())
                continue;
        }
        if (line[0] != '+' && line[0] != '-' && line[0] != '[')
        {
            throw std::runtime_error("Invalid token at the begining of line in config file! Each line should begin with ether '+' "
                                     "or '-' or '#'! Line: " +
                                     line);
        }
        if (line[0] == '[')
        {
            if (line.substr(1).starts_with("setup"))
            {
                initBlock = InitBlock::SETUP;
            }
            else
            {
                initBlock = InitBlock::LISTS;
            }
            continue;
        }

        /// FIXME exclude filters
        bool _unused_doRegister = line[0] == '+' ? true : false;
        size_t space            = line.find(' ');
        if (space == std::string::npos)
        {
            throw std::runtime_error("Invalid line in config file! Each line must have token separated with space from object "
                                     "name. For example: '+function aaa::bb::my_function'. Line: " +
                                     line);
        }

        std::string nodeName            = line.substr(1, space - 1);
        std::string name                = line.substr(space + 1);
        std::string name_without_spaces = name;
        name_without_spaces.erase(std::remove(name_without_spaces.begin(), name_without_spaces.end(), ' '),
                                  name_without_spaces.end());

        if (initBlock == InitBlock::SETUP)
        {
            if (nodeName == "rootClass")
            {
                rootClassName = name_without_spaces;
            }
            if (nodeName == "include")
            {
                outputInclude = name_without_spaces;
            }
        }
        else
        {
            Logger::get().info("requested ClassItem: " + name + " under node: " + nodeName);
            RegisterRequest request;
            request.classItem = name;
            request.node      = nodeName;
            m_register.push_back(request);
        }
    }
}

const Config::t_register& Config::getRegisters() const
{
    return m_register;
}

// std::pair<bool, RegisterRequest*> Config::doRegister_classField(const std::string& name)
bool Config::doRegister_classField(const std::string& name)
{
    for (auto& it : m_register)
    {
        if (it.classItem == name)
        {
            if (!it.isMatched)
            {
                it.isMatched = true;
                return true;
            }
            Logger::get().warn("duplicate match attempted: " + it.classItem);
            return false;  // std::make_pair(true, &it);
        }
    }
    return false;  // std::make_pair(false, nullptr);
}

const RegisterRequest* Config::getRequest(const std::string& name)
{
    for (const auto& it : m_register)
    {
        if (it.classItem == name)
        {
            return &it;
        }
    }
    return nullptr;
}