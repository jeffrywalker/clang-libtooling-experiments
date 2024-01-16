#pragma once
#include <string>
#include <utility>
#include <vector>

namespace clang
{
    class FieldDecl;
    class Type;
    class QualType;
    class ASTContext;
}  // namespace clang

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
    /// TODO handling how std::array is registered i.e., don't use _Elems
    class RegisteredVariable
    {
        /// TODO list name different from actual name, example: m_inp -> INP
            public:
        /// container for entries of an enumeration
        typedef std::vector<std::pair<std::string, int>> EnumEntries;

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
        /// name of the parent class (if applicable)
        std::string className = "";
        /// indicates value is a built-in variable or enumeration
        /// these are the end nodes that register with memory address
        bool isClass   = false;
        bool isStruct  = false;
        bool isEnum    = false;
        bool isBuiltIn = false;
        bool isArray   = false;
        bool isPointer = false;
        /// TODO accesss criteria may be needed for use with (library) classes

        /// dimensions of the array
        std::vector<uint64_t> dimensions;

        /// \returns number of array elements this variable has
        size_t getNumArrayElements() const;
        /// \param index the linear index into the array
        std::string getArrayAccessFromLinearIndex(size_t index) const;

        /// \returns true if the comment specified unit entry is 'inherit'
        bool inheritsUnits();

        /// \returns the VarType enum string for the given type
        std::string getVarTypeEnumString(const std::string& arrayAccess = "") const;
        /// \returns string used to access this variable address
        std::string getAddressAccess(const std::string& arrayAccess = "") const;
        std::string getArrayDesignation() const;

        /// entries of the enumeration (if applicable)
        EnumEntries enumEntries;
        /// \returns the appropraite string to register this enumeration
        std::string getEnumRegistrationCode() const;


        /// updates the entry with the provided FieldDecl
        /// Sets:
        ///     * name
        ///     * is class, struct, enum, basicType
        ///     * typeName
        ///     * enumName
        ///     * convention from enum (or comments)
        /// Sets from comments:
        ///     * units
        ///     * range
        ///     * convention (will overwrite enum if supplied)
        ///     * description
        ///     * defaultValue (TODO questionable utility)
        /// \returns true if successful
        bool update(const clang::FieldDecl* fd, const std::string& list_name, const RegisteredVariable* parent = nullptr);

        /// TODO clarify method name
        /// \note this is the access name
        /// \returns the full name as determied by the prescribed parent node
        std::string getFullName(const std::string& arrayAccess = "") const;
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
        std::string getListVarName(const std::string& arrayAccess = "") const;

        /// dump contents to std::cout
        void dump();
        /// \returns registration string for this entity
        std::string getRegistrationCode() const;

        std::string getBuiltInTypeStr(const clang::Type* t, clang::ASTContext& context) const;

        /// sets the active array access
        void setActiveArrayAccess(size_t index);
        void clearActiveArrayAccess();

            private:
        /// fully qualified name used to obtain memory address
        std::string m_fullQualName = "";
        /// fully qualified list name
        std::string m_listName = "";
        /// name of the variable
        std::string m_name = "";
        /// current array access
        std::string m_activeArrayAccess = "";

        /// applies filtering to name
        /// HACK assumes 'm_' should always be removed
        /// TODO needs to be configurable
        std::string getFilteredName();

        std::string getAddRefCode() const;
        std::string getAddVarCode(const std::string& arrayAccess = "") const;

        void updateTypeInfo(clang::ASTContext& context, const clang::Type* t, const clang::QualType* qt = nullptr,
                            bool is_array = false);
    };
}  // namespace data_registration