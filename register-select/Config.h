#pragma once

#include <memory>
#include <string>
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

    class Config
    {
            public:
        typedef std::vector<RegisterRequest> t_register;

        static Config& get();
        /// Read config setting from the file
        /// TODO JSON withh schema
        void read(const std::string& file_name);

        /// output filename to write registration code to
        /// TODO support splitting up code
        std::string outputFileName = "";
        std::string outputDir      = "";
        std::string outputInclude  = "";
        /// class that owns the registration method
        std::string rootClassName = "";

        // std::pair<bool, RegisterRequest*> doRegister_classField(const std::string& name);
        bool doRegister_classField(const std::string& name);
        const RegisterRequest* getRequest(const std::string& name);

        const t_register& getRegisters() const;

            private:
        Config();

        /// lists to be registered
        t_register m_register;
    };

    // REMOVE typedef std::shared_ptr<RegisterRequest> spRegisterRequest;
}  // namespace data_registration