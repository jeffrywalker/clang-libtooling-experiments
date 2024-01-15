#pragma once

#include <source_location>
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

        void debug(const std::string& msg, const std::source_location location = std::source_location::current());
        void info(const std::string& msg, const std::source_location location = std::source_location::current());
        void warn(const std::string& msg, const std::source_location location = std::source_location::current());
        void error(const std::string& msg, const std::source_location location = std::source_location::current());

            private:
        Logger();
        LogLevel m_logLevel = LogLevel::INFO;
        void write(const std::string& msg, const std::source_location, LogLevel);
    };
}  // namespace data_registration