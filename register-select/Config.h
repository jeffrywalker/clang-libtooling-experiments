#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace data_registration
{
    /// container for requested registration
    struct RegisterRequest
    {
        /// class item to be registered
        std::string classItem;
        /// top level list the item is in
        std::string listName;
        /// root node within the list, "INP", "OUT", "INT", "Monitor"
        std::string node;
        /// indicates if this request has been found
        bool isMatched = false;
    };

    /// TODO unit replacements
    /// TODO exclude class filters
    /// TODO register of classes that have private data - register method access
    /// TODO support of arrays
    /// TODO hash of registration code
    /// TODO support splitting up registration code into functions
    class Config
    {
            public:
        typedef std::vector<RegisterRequest> t_register;
        Config(const Config& old) = delete;

        static Config& get();
        /// Read config setting from the file
        /// TODO JSON withh schema
        void read(const std::string& file_name);

        /// output filename to write registration code to
        std::string outputFileName = "";
        std::string outputDir      = "";
        std::string outputInclude  = "";
        /// class that owns the registration method
        std::string rootClassName = "";

        /// \note This method is intended for use with implict inclusions. For example a field that is a class
        /// which itself may have items that are not intended for registration.
        ///
        /// True when:
        ///     * a filter does not exists for the class
        ///     * a + entry exists for the field
        /// TODO logic for the opposite, "-"
        /// \param [in] classFieldName class::field that is to be registered
        /// \returns true if item should be registered
        bool doRegisterImplicitClassField(const std::string& classFieldName);

        /// \note This check is for the explicit list entries
        /// \param [in] name class::field entry as it appears in the config file
        /// \returns true if this item is to be included
        bool doRegister_classField(const std::string& name);
        const RegisterRequest* getRequest(const std::string& name);

        const t_register& getRegisters() const;

            private:
        static Config* m_instance;
        Config();

        /// lists to be registered
        t_register m_register;

        /// list of class filters to not include
        std::unordered_set<std::string> m_classIncludeFilters;
    };

    // REMOVE typedef std::shared_ptr<RegisterRequest> spRegisterRequest;
}  // namespace data_registration