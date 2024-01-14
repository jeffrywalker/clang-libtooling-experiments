#pragma once
#include <string>

namespace data_registration
{
    /// keyword that indicates units are inherited
    const char* const INHERIT_UNIT = "inherit";
    /// doxygen keyword for units
    const char* const UNITS_KEYWORD = "units";
    /// doxygen keyword for range
    const char* const RANGE_KEYWORD = "range";
    /// doxygen keyword for convention
    const char* const CONVENTION_KEYWORD = "convention";
    /// doxygen keyword for description (optional)
    const char* const DESCRIPTION_KEYWORD = "description";

    /// Container for a single registered variable
    class RegisteredVariable
    {
            public:
        /// fully qualified name
        std::string fullQualName = "";
        /// name of the variable
        std::string name = "";
        /// units affiliated with the variable
        /// example: \units ft
        std::string units = "";
        /// range of the data
        /// example: \range [-180, 180]
        std::string range = "";
        /// convention for the variable
        /// example: \convention +down
        std::string convention = "";
        /// description of this entity
        std::string description = "";
        /// the default value associated with the variable
        std::string defaultValue = "";
        /// the variable type name
        std::string typeName = "";
        /// name of the enumeration (if applicable)
        std::string enumName = "";
        /// name of the parent struct (if applicable)
        std::string structName = "";

        /// processes any given keyword and assigns recognized items
        /// \param [in] keyword "\keyword" from comment
        /// \param [in] value string following the keyword
        void processKeyword(const std::string& keyword, const std::string& value);

        /// sets the description to text provided text is not empty and description is empty
        void setDescriptionFromText(const std::string& text);

        /// dump contents to std::cout
        void dump();
    };
}  // namespace data_registration