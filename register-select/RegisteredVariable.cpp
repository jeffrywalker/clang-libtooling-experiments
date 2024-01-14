#include "RegisteredVariable.h"
#include <format>
#include <iostream>
#include <string_view>

using namespace data_registration;

const std::string WHITESPACE = " \n\r\t\f\v";

// const char* data_registration::INHERIT_UNIT = "inherit";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

void RegisteredVariable::processKeyword(const std::string& keyword, const std::string& value)
{
    if (keyword == UNITS_KEYWORD)
    {
        units = trim(value);
    }
    if (keyword == RANGE_KEYWORD)
    {
        range = trim(value);
    }
    if (keyword == CONVENTION_KEYWORD)
    {
        convention = trim(value);
    }
    if (keyword == DESCRIPTION_KEYWORD)
    {
        description = trim(value);
    }
}

void RegisteredVariable::setDescriptionFromText(const std::string& text)
{
    if (description != "")
    {
        return;
    }
    /// FIXME this doesn't capture tabs
    if (text.find_first_not_of(WHITESPACE) != std::string::npos)
    {
        description = trim(text);
    }
}

void RegisteredVariable::setName(const std::string& name)
{
    m_name         = name;
    m_fullQualName = name;

    m_listName = std::format("{}.{}", listName, getFilteredName());
}

std::string RegisteredVariable::getFilteredName()
{
    std::string _name = m_name;
    if (_name.starts_with("m_"))
    {
        _name = _name.substr(2);
    }
    return _name;
}

void RegisteredVariable::setParent(const RegisteredVariable* parent)
{
    /// FIXME assumes no pointers or methods
    m_fullQualName = parent->getFullName() + "." + m_fullQualName;
    m_listName     = parent->getListVarName() + "." + getFilteredName();
}

const std::string& RegisteredVariable::getName() const
{
    return m_name;
}

const std::string& RegisteredVariable::getListVarName() const
{
    return m_listName;
}

const std::string& RegisteredVariable::getFullName() const
{
    return m_fullQualName;
}

std::string RegisteredVariable::dumpStr()
{
    std::string type_str = typeName;
    if (type_str == "")
    {
        type_str = "(ENUM) " + enumName;
    }

    std::string defaultValue     = "";
    std::string arrayDesignation = "";
    /// TODO need to check for when &() is needed
    if (isBasicType)
    {
        return std::format("registerVar(L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", &({}));\n", getListVarName(),
                           description, units, convention, defaultValue, range, type_str, getFullName());
    }
    else
    {
        return std::format("registerReference(L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\", L\"{}\");\n",
                           getListVarName(), arrayDesignation, description, units, convention, defaultValue, range, type_str);
    }
}

void RegisteredVariable::dump()
{
    std::cout << dumpStr();
}