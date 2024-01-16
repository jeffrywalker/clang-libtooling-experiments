#include "str_utils.h"

using namespace str_utils;
using std::string;

const string str_utils::WHITESPACE = " \n\r\t\f\v";

string str_utils::ltrim(const string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string str_utils::rtrim(const string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string str_utils::trim(const string& s)
{
    return rtrim(ltrim(s));
}

std::vector<string> str_utils::split(const string& s, const string& delimiter, bool discardEmpty)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    std::vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token     = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (discardEmpty)
        {
            token = trim(token);
            if (!token.empty())
                res.push_back(token);
        }
        else
        {
            res.push_back(token);
        }
    }
    if (discardEmpty)
    {
        token = trim(s.substr(pos_start));
        if (!token.empty())
            res.push_back(token);
    }
    else
    {
        res.push_back(token);
    }

    return res;
}


string str_utils::base_namespace(const string& ns)
{
    size_t f = ns.rfind("::");
    if (f == string::npos)
        return "";
    else
        return ns.substr(0, f);
}

string str_utils::last_namespace(const string& ns)
{
    size_t f = ns.rfind("::");
    if (f == string::npos)
        return ns;
    else
        return ns.substr(f + 2, ns.size() - f - 2);
}

string str_utils::indent(const string& s, const string& indent)
{
    // split without alteration
    auto lines = split(s, "\n", false);
    string r;
    for (auto& l : lines)
    {
        r += l.size() ? indent + l + '\n' : l + '\n';
    }
    return r;
}

string str_utils::tab(int n, int nspace)
{
    string tab;
    tab.append(n * nspace, ' ');
    return tab;
}