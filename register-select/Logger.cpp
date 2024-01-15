#include "Logger.h"
#include <iostream>

using namespace data_registration;

Logger::Logger()
{
}

Logger& Logger::get()
{
    static Logger* instance = nullptr;
    if (!instance)
    {
        instance = new Logger();
    }
    return *instance;
}

void Logger::setLogLevel(LogLevel level)
{
    m_logLevel = level;
}

void Logger::write(const std::string& msg, const std::source_location location, LogLevel level)
{
    std::stringstream ss;
    switch (level)
    {
        case LogLevel::DEBUG:
            ss << "DEBUG: ";
            break;
        case LogLevel::INFO:
            ss << "INFO: ";
            break;
        case LogLevel::WARNING:
            ss << "WARNING: ";
            break;
        case LogLevel::ERROR:
            ss << "ERROR: ";
            break;
    }
    ss << msg;
    if (level != LogLevel::INFO)
    {
        ss << "\n    " << location.file_name() << "(" << location.line() << "," << location.column() << ")\n"
           << "    " << location.function_name();
    }
    std::cout << ss.str() << "\n";
}

void Logger::debug(const std::string& msg, const std::source_location location /*= std::source_location::current()*/)
{
    if (m_logLevel <= LogLevel::DEBUG)
    {
        write(msg, location, LogLevel::DEBUG);
    }
}
void Logger::info(const std::string& msg, const std::source_location location /*= std::source_location::current()*/)
{
    if (m_logLevel <= LogLevel::INFO)
    {
        write(msg, location, LogLevel::INFO);
    }
}

void Logger::warn(const std::string& msg, const std::source_location location /*= std::source_location::current()*/)
{
    if (m_logLevel <= LogLevel::WARNING)
    {
        write(msg, location, LogLevel::WARNING);
    }
}

void Logger::error(const std::string& msg, const std::source_location location /*= std::source_location::current()*/)
{
    if (m_logLevel <= LogLevel::ERROR)
    {
        write(msg, location, LogLevel::ERROR);
    }
}