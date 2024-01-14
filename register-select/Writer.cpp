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
    return true;
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