#include "RegisteredVariable.h"
#include <iostream>

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
    if (text.find_first_not_of(WHITESPACE) != std::string::npos)
    {
        description = trim(text);
    }
}

void RegisteredVariable::dump()
{
    std::string type_str = typeName;
    if (type_str == "")
    {
        type_str = "(ENUM) " + enumName;
    }
    std::cout << "name: " << name << "\n"
              << "  type: " << type_str << "\n"
              << "  description: " << description << "\n"
              << "  units: " << units << "\n"
              << "  range: " << range << "\n"
              << "  convention: " << convention << "\n";
}