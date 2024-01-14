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

void Logger::write(const std::string& msg)
{
    std::cout << msg << "\n";
}

void Logger::debug(const std::string& msg)
{
    if (m_logLevel <= LogLevel::DEBUG)
    {
        write("DEBUG: " + msg);
    }
}
void Logger::info(const std::string& msg)
{
    if (m_logLevel <= LogLevel::INFO)
    {
        write("INFO: " + msg);
    }
}

void Logger::warn(const std::string& msg)
{
    if (m_logLevel <= LogLevel::WARNING)
    {
        write("WARNING: " + msg);
    }
}

void Logger::error(const std::string& msg)
{
    if (m_logLevel <= LogLevel::ERROR)
    {
        write("ERROR: " + msg);
    }
}