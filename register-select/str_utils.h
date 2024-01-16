#pragma once
#include <string>
#include <vector>

namespace str_utils
{
    /// defines pattern for whitespace
    extern const std::string WHITESPACE;

    /// creates tab using spaces
    /// \param n number of tabs
    /// \param nspace number of spaces that defines a single tab
    std::string tab(int n = 1, int nspace = 4);

    /// splits the string by the delimiter
    /// \param [in] s string to split
    /// \param [in] delimiter to split on
    /// \param [in] discardEmpty when true whitespace only entries are removed
    std::vector<std::string> split(const std::string& s, const std::string& delimiter, bool discardEmpty = true);

    /// indents string using prescribed indent prefix
    std::string indent(const std::string& s, const std::string& indent);

    /// Calculate base (upper) namespace for given one: a::b::c --> a::b
    std::string base_namespace(const std::string& ns);

    /// Calculate last namespace for given one: core::pose::motif --> motif
    std::string last_namespace(const std::string& ns);

    /// split string by delimiter
    std::vector<std::string> split(const std::string& s, const std::string& delimiter);

    /// trim leading whitespace
    std::string ltrim(const std::string& s);

    /// trim trailing whitespace
    std::string rtrim(const std::string& s);

    /// trim leading and trailing whitespace
    std::string trim(const std::string& s);
}  // namespace str_utils