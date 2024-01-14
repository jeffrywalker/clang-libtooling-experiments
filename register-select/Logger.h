#pragma once

#include <sstream>
#include <string>

namespace data_registration
{
    class Logger
    {
            public:
        enum LogLevel
        {
            NOTSET  = 0,
            DEBUG   = 10,
            INFO    = 20,
            WARNING = 30,
            ERROR   = 40
        };

        static Logger& get();

        void setLogLevel(LogLevel level);

        void debug(const std::string& msg);
        void info(const std::string& msg);
        void warn(const std::string& msg);
        void error(const std::string& msg);

            private:
        Logger();
        LogLevel m_logLevel = LogLevel::INFO;
        void write(const std::string& msg);
    };
}  // namespace data_registration