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
        /// TODO list name different from actual name, example: m_inp -> INP
            public:
        std::string listName = "";
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
        /// indicates value is a built-in variable
        /// these are the end nodes that register with memory address
        bool isBasicType = false;

        /// \returns the full name as determied by the prescribed parent node
        const std::string& getFullName() const;
        /// \returns the variable name
        const std::string& getName() const;

        /// \param [in] parent variable
        void setParent(const RegisteredVariable* parent);
        /// \param [in] name the variable name
        void setName(const std::string& name);

        /// processes any given keyword and assigns recognized items
        /// \param [in] keyword "\keyword" from comment
        /// \param [in] value string following the keyword
        void processKeyword(const std::string& keyword, const std::string& value);

        /// sets the description to text provided text is not empty and description is empty
        void setDescriptionFromText(const std::string& text);

        /// \returns the variable name as it should appear in the list
        const std::string& getListVarName() const;

        /// dump contents to std::cout
        void dump();
        /// \returns registration string for this entity
        std::string dumpStr();

            private:
        /// fully qualified name used to obtain memory address
        std::string m_fullQualName = "";
        /// fully qualified list name
        std::string m_listName = "";
        /// name of the variable
        std::string m_name = "";

        /// applies filtering to name
        /// HACK assumes 'm_' should always be removed
        /// TODO needs to be configurable
        std::string getFilteredName();
    };
}  // namespace data_registration