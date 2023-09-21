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

    /// \register x
    double* _px();
    /// \register y
    double* _py();
    /// \register z
    double* _pz();

        private:
    std::array<double, 3> m_xyz = {0};
};