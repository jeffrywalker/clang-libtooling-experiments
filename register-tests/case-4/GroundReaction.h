#include "LandingGear.h"
#include "MathTypes.h"

namespace ns_GroundReaction
{
    struct INP
    {
        /// \units ft
        double alt;
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
    struct INT
    {
    };

    typedef DataBase<INP, OUT, INT> ModelData;

    struct Experimental
    {
        double expTest_1;
        double expTest_2;
        bool isExperimental;
    };
}  // namespace ns_GroundReaction


class GroundReaction : public ns_GroundReaction::ModelData, protected ns_GroundReaction::Experimental
{
    bool registerData(const std::wstring& listName, IVarData* pVarData);

    LandingGear leftGear;
    LandingGear rightGear;
    LandingGear noseGear;

    struct JunkData
    {
        int junkVar1;
        bool isJunk;
        double junkFloat;
    };
    JunkData junk;
};