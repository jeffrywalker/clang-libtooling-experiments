#include "Vector3.h"

void Vector3::x(double x)
{
    m_xyz[0] = x;
}

void Vector3::y(double y)
{
    m_xyz[1] = y;
}

void Vector3::z(double z)
{
    m_xyz[2] = z;
}

double Vector3::x() const
{
    return m_xyz[0];
}

double Vector3::y() const
{
    return m_xyz[1];
}

double Vector3::z() const
{
    return m_xyz[2];
}

double* Vector3::px()
{
    return &m_xyz[0];
}

double* Vector3::py()
{
    return &m_xyz[1];
}

double* Vector3::pz()
{
    return &m_xyz[2];
}