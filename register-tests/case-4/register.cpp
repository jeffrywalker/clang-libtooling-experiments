#include "GroundReaction.h"
#include <string>
#include <chrono>
#include <vector>
#include <utility>

// HACK
class IVarDef {
public:
    enum vartype { ENUM };
    template <typename T> static vartype getVarType(T var){}
};
// HACK
class IVarList {
public:
    void addReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName)
    {}
    void addVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, IVarDef::vartype varType, void* address, const wchar_t* enumName = nullptr)
    {}
    bool checkForChange(const wchar_t*){}
    void alignToList(IVarList*){}
    IVarList* createComparisonList(){}
};
// HACK
class IVarData {
public:
    IVarList* getList(const wchar_t* name){}
    IVarList* createVarList(const wchar_t* name, unsigned int* r=(unsigned int*)nullptr){}
};


bool GroundReaction::registerData(const std::wstring& listName, IVarData* pVarData)
{
    // HACK always unique hash
    std::wstring hack_changingHash = listName + std::to_wstring(std::chrono::steady_clock().now().time_since_epoch().count());
    IVarList* pvl = pVarData->getList(listName.c_str());
    IVarList* pvl_old = pvl;
    bool doAlign = false;
    if (pvl != nullptr)
    {
        if (pvl->checkForChange(hack_changingHash.c_str()))
        {
            pvl = pvl->createComparisonList();
            doAlign = true;
        }
    }
    if (pvl == nullptr)
    {
        pvl = pVarData->createVarList(listName.c_str());
        if (pvl == nullptr)
            return false;
        pvl->checkForChange(hack_changingHash.c_str());
    }

    pvl->addVar(L"INP.alt",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(alt),
        /*address*/ &(alt));
    pvl->addVar(L"INP.velocity",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(velocity),
        /*address*/ &(velocity));
    pvl->addReference(L"OUT.forces",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"OUT.forces.x",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(forces.x),
        /*address*/ &(forces.x));
    pvl->addVar(L"OUT.forces.y",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(forces.y),
        /*address*/ &(forces.y));
    pvl->addVar(L"OUT.forces.z",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(forces.z),
        /*address*/ &(forces.z));
    pvl->addReference(L"OUT.moments",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"OUT.moments.x",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(moments.x),
        /*address*/ &(moments.x));
    pvl->addVar(L"OUT.moments.y",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(moments.y),
        /*address*/ &(moments.y));
    pvl->addVar(L"OUT.moments.z",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(moments.z),
        /*address*/ &(moments.z));
    pvl->addVar(L"DEV.expTest_1",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(expTest_1),
        /*address*/ &(expTest_1));
    pvl->addVar(L"DEV.expTest_2",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(expTest_2),
        /*address*/ &(expTest_2));
    pvl->addVar(L"DEV.isExperimental",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(isExperimental),
        /*address*/ &(isExperimental));
    pvl->addReference(L"INT.leftGear",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"LandingGear");
    pvl->addReference(L"INT.leftGear.position",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.leftGear.position.x",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.position.x),
        /*address*/ &(leftGear.position.x));
    pvl->addVar(L"INT.leftGear.position.y",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.position.y),
        /*address*/ &(leftGear.position.y));
    pvl->addVar(L"INT.leftGear.position.z",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.position.z),
        /*address*/ &(leftGear.position.z));
    pvl->addVar(L"INT.leftGear.velocity",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.velocity),
        /*address*/ &(leftGear.velocity));
    pvl->addReference(L"INT.leftGear.forces",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.leftGear.forces.x",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.forces.x),
        /*address*/ &(leftGear.forces.x));
    pvl->addVar(L"INT.leftGear.forces.y",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.forces.y),
        /*address*/ &(leftGear.forces.y));
    pvl->addVar(L"INT.leftGear.forces.z",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.forces.z),
        /*address*/ &(leftGear.forces.z));
    pvl->addReference(L"INT.leftGear.moments",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.leftGear.moments.x",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.moments.x),
        /*address*/ &(leftGear.moments.x));
    pvl->addVar(L"INT.leftGear.moments.y",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.moments.y),
        /*address*/ &(leftGear.moments.y));
    pvl->addVar(L"INT.leftGear.moments.z",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.moments.z),
        /*address*/ &(leftGear.moments.z));
    pvl->addVar(L"INT.leftGear.frameCount",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.frameCount),
        /*address*/ &(leftGear.frameCount));
    pvl->addReference(L"INT.leftGear.leftTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.leftGear.leftTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.leftTire.radius),
        /*address*/ &(leftGear.leftTire.radius));
    pvl->addVar(L"INT.leftGear.leftTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.leftTire.pressure),
        /*address*/ &(leftGear.leftTire.pressure));
    pvl->addVar(L"INT.leftGear.leftTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.leftTire.isFlat),
        /*address*/ &(leftGear.leftTire.isFlat));
    pvl->addReference(L"INT.leftGear.rightTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.leftGear.rightTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.rightTire.radius),
        /*address*/ &(leftGear.rightTire.radius));
    pvl->addVar(L"INT.leftGear.rightTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.rightTire.pressure),
        /*address*/ &(leftGear.rightTire.pressure));
    pvl->addVar(L"INT.leftGear.rightTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(leftGear.rightTire.isFlat),
        /*address*/ &(leftGear.rightTire.isFlat));
    pvl->addReference(L"INT.rightGear",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"LandingGear");
    pvl->addReference(L"INT.rightGear.position",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.rightGear.position.x",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.position.x),
        /*address*/ &(rightGear.position.x));
    pvl->addVar(L"INT.rightGear.position.y",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.position.y),
        /*address*/ &(rightGear.position.y));
    pvl->addVar(L"INT.rightGear.position.z",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.position.z),
        /*address*/ &(rightGear.position.z));
    pvl->addVar(L"INT.rightGear.velocity",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.velocity),
        /*address*/ &(rightGear.velocity));
    pvl->addReference(L"INT.rightGear.forces",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.rightGear.forces.x",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.forces.x),
        /*address*/ &(rightGear.forces.x));
    pvl->addVar(L"INT.rightGear.forces.y",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.forces.y),
        /*address*/ &(rightGear.forces.y));
    pvl->addVar(L"INT.rightGear.forces.z",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.forces.z),
        /*address*/ &(rightGear.forces.z));
    pvl->addReference(L"INT.rightGear.moments",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.rightGear.moments.x",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.moments.x),
        /*address*/ &(rightGear.moments.x));
    pvl->addVar(L"INT.rightGear.moments.y",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.moments.y),
        /*address*/ &(rightGear.moments.y));
    pvl->addVar(L"INT.rightGear.moments.z",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.moments.z),
        /*address*/ &(rightGear.moments.z));
    pvl->addVar(L"INT.rightGear.frameCount",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.frameCount),
        /*address*/ &(rightGear.frameCount));
    pvl->addReference(L"INT.rightGear.leftTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.rightGear.leftTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.leftTire.radius),
        /*address*/ &(rightGear.leftTire.radius));
    pvl->addVar(L"INT.rightGear.leftTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.leftTire.pressure),
        /*address*/ &(rightGear.leftTire.pressure));
    pvl->addVar(L"INT.rightGear.leftTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.leftTire.isFlat),
        /*address*/ &(rightGear.leftTire.isFlat));
    pvl->addReference(L"INT.rightGear.rightTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.rightGear.rightTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.rightTire.radius),
        /*address*/ &(rightGear.rightTire.radius));
    pvl->addVar(L"INT.rightGear.rightTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.rightTire.pressure),
        /*address*/ &(rightGear.rightTire.pressure));
    pvl->addVar(L"INT.rightGear.rightTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(rightGear.rightTire.isFlat),
        /*address*/ &(rightGear.rightTire.isFlat));
    pvl->addReference(L"INT.noseGear",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"LandingGear");
    pvl->addReference(L"INT.noseGear.position",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.noseGear.position.x",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.position.x),
        /*address*/ &(noseGear.position.x));
    pvl->addVar(L"INT.noseGear.position.y",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.position.y),
        /*address*/ &(noseGear.position.y));
    pvl->addVar(L"INT.noseGear.position.z",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.position.z),
        /*address*/ &(noseGear.position.z));
    pvl->addVar(L"INT.noseGear.velocity",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.velocity),
        /*address*/ &(noseGear.velocity));
    pvl->addReference(L"INT.noseGear.forces",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.noseGear.forces.x",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.forces.x),
        /*address*/ &(noseGear.forces.x));
    pvl->addVar(L"INT.noseGear.forces.y",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.forces.y),
        /*address*/ &(noseGear.forces.y));
    pvl->addVar(L"INT.noseGear.forces.z",
        /*description*/ L"",
        /*units*/ L"N",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.forces.z),
        /*address*/ &(noseGear.forces.z));
    pvl->addReference(L"INT.noseGear.moments",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vector3");
    pvl->addVar(L"INT.noseGear.moments.x",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.moments.x),
        /*address*/ &(noseGear.moments.x));
    pvl->addVar(L"INT.noseGear.moments.y",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.moments.y),
        /*address*/ &(noseGear.moments.y));
    pvl->addVar(L"INT.noseGear.moments.z",
        /*description*/ L"",
        /*units*/ L"N*m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.moments.z),
        /*address*/ &(noseGear.moments.z));
    pvl->addVar(L"INT.noseGear.frameCount",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.frameCount),
        /*address*/ &(noseGear.frameCount));
    pvl->addReference(L"INT.noseGear.leftTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.noseGear.leftTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.leftTire.radius),
        /*address*/ &(noseGear.leftTire.radius));
    pvl->addVar(L"INT.noseGear.leftTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.leftTire.pressure),
        /*address*/ &(noseGear.leftTire.pressure));
    pvl->addVar(L"INT.noseGear.leftTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.leftTire.isFlat),
        /*address*/ &(noseGear.leftTire.isFlat));
    pvl->addReference(L"INT.noseGear.rightTire",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Tire");
    pvl->addVar(L"INT.noseGear.rightTire.radius",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.rightTire.radius),
        /*address*/ &(noseGear.rightTire.radius));
    pvl->addVar(L"INT.noseGear.rightTire.pressure",
        /*description*/ L"",
        /*units*/ L"lbf/in^2",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.rightTire.pressure),
        /*address*/ &(noseGear.rightTire.pressure));
    pvl->addVar(L"INT.noseGear.rightTire.isFlat",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(noseGear.rightTire.isFlat),
        /*address*/ &(noseGear.rightTire.isFlat));
    if (doAlign)
        pvl_old->alignToList(pvl);
    // pVarList = pvl;
    return true;
}