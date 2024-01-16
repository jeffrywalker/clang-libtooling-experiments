#pragma once
#include <fstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Config.h"
#include "DataRegister.h"

namespace data_registration
{
    /// root owner of writing data registration code
    class Context
    {
            public:
        Context();
        /// generates the registration code
        void generate(const Config& config);

        /// adds the DataRegister entry to the list to be created
        void add(spDataRegister& dataRegisterSp, const std::string& classItem);

        /// \param enumName name to register, duplicates blocked
        /// \param enumCode registration code to write
        void registerEnum(const std::string& enumName, const std::string& enumCode);

            private:
        /// all root items from translation unit to be registered
        std::vector<std::pair<spDataRegister, std::string>> m_rootRegisters;
        // std::vector<spDataRegister> m_rootRegisters;

        /// unique IDs of items to be created
        std::unordered_set<std::string> m_ids;
        /// unique enumeration IDs to prevent duplicates
        std::unordered_set<std::string> m_enumIds;
    };
}  // namespace data_registration