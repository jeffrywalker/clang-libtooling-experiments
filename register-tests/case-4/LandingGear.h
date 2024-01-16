#include "MathTypes.h"
#pragma once


namespace ns_LandingGear
{
    struct INP
    {
        /// \units ft
        math::Vector3 position;
        /// \units ft/s
        double velocity;
    };

    struct OUT
    {
        /// \units N
        math::Vector3 forces;
        /// \units N*m
        math::Vector3 moments;
    };
    struct Tire
    {
        /// \units ft
        double radius;
        /// \units lbf/in^2
        double pressure;
        bool isFlat;
    };
    struct INT
    {
        int frameCount;
        Tire leftTire;
        Tire rightTire;
    };

    typedef DataBase<INP, OUT, INT> ModelData;

    struct Sandbox
    {
        double sandbox_a;
        double sandbox_b;
        double sandbox_c;
    };

}  // namespace ns_LandingGear


class LandingGear : public ns_LandingGear::ModelData, public ns_LandingGear::Sandbox
{
        public:
    struct DebugData
    {
        /// \units ft/s^2
        math::Vector3 acceleration;
        bool hasContact;
    };
    /// DoNotRegister
    double junkVar;
    /// DoNotRegister
    bool isInReset;

    /// DoNotRegister
    DebugData m_devDebug;
};