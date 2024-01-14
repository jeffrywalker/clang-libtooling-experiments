#pragma once

#include <fstream>

namespace data_registration
{
    class Writer
    {
            public:
        static Writer& get();
        bool openFile(const std::string& fileName);
        bool close();
        bool write(const std::string& s);

            private:
        std::ofstream m_out;
    };
}  // namespace data_registration