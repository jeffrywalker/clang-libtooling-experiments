#include "Writer.h"

using namespace data_registration;

Writer& Writer::get()
{
    static Writer* instance = nullptr;
    if (!instance)
    {
        instance = new Writer();
    }
    return *instance;
}

bool Writer::openFile(const std::string& fileName)
{
    if (m_out.is_open())
    {
        return false;
    }
    m_out.open(fileName);
    m_enum.clear();
    m_register.clear();
    return true;
}
void Writer::writeEnum()
{
    m_out << m_enum.str();
    m_enum.clear();
}
void Writer::writeRegister()
{
    m_out << m_register.str();
    m_register.clear();
}
void Writer::bufferEnum(const std::string& s)
{
    m_enum << s;
}
void Writer::bufferRegister(const std::string& s)
{
    m_register << s;
}

bool Writer::close()
{
    m_out.close();
    return true;
}

bool Writer::write(const std::string& s)
{
    if (!m_out.is_open())
    {
        return false;
    }
    m_out << s;
    return true;
}