#pragma once

#include <fstream>
#include <sstream>
namespace data_registration
{
    class Writer
    {
            public:
        static Writer& get();
        Writer(const Writer& old) = delete;
        bool openFile(const std::string& fileName);
        bool close();
        /// direct write to opened stream
        bool write(const std::string& s);
        /// write to enum buffer
        void bufferEnum(const std::string& s);
        /// write to register buffer
        void bufferRegister(const std::string& s);

        void writeEnum();
        void writeRegister();

            private:
        Writer();
        static Writer* m_instance;
        std::string m_activeFile;

        std::ofstream m_out;

        std::stringstream m_enum;
        std::stringstream m_register;
    };
}  // namespace data_registration