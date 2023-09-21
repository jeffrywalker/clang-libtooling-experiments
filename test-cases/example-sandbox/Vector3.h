#pragma once
#include <array>

class Vector3
{
        public:
    void x(double x);
    void y(double y);
    void z(double z);

    double x() const;
    double y() const;
    double z() const;

    // expose pointers for registration
    double* px();
    double* py();
    double* pz();

        private:
    std::array<double, 3> m_xyz = {0};
};