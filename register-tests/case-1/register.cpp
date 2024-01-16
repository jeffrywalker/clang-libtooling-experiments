#include "Parent.h"
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


bool Parent::registerData(const std::wstring& listName, IVarData* pVarData)
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

{
    std::vector<std::pair<std::wstring, int>> entryList = 
    {
        {L"OFF", 0},
        {L"ON", 1},
        {L"IDLE", 2},
    };
    string_utils::registerEnum(std::wstring(L"Mode"), entryList);
}
    pvl->addReference(L"INP.inp",
        /*array*/ L"",
        /*description*/ L"system input data",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Inputs");
    pvl->addVar(L"INP.inp.u",
        /*description*/ L"primary input",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_inp.u),
        /*address*/ &(m_inp.u));
    pvl->addVar(L"INP.inp.mode",
        /*description*/ L"operational mode",
        /*units*/ L"",
        /*convention*/ L"OFF(0) ON(1) IDLE(2) ",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::ENUM,
        /*address*/ &(m_inp.mode),
        /*enum*/ L"Mode");
    pvl->addReference(L"OUT.out",
        /*array*/ L"",
        /*description*/ L"system output data",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Outputs");
    pvl->addVar(L"OUT.out.y",
        /*description*/ L"y output",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.y),
        /*address*/ &(m_out.y));
    pvl->addReference(L"OUT.out.position",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"OUT.out.position.x",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.position.x),
        /*address*/ &(m_out.position.x));
    pvl->addVar(L"OUT.out.position.y",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.position.y),
        /*address*/ &(m_out.position.y));
    pvl->addVar(L"OUT.out.position.z",
        /*description*/ L"",
        /*units*/ L"ft",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.position.z),
        /*address*/ &(m_out.position.z));
    pvl->addReference(L"OUT.out.myVehicle",
        /*array*/ L"",
        /*description*/ L"my vehicle",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vehicle");
    pvl->addVar(L"OUT.out.myVehicle.foo",
        /*description*/ L"the power of foo",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.foo),
        /*address*/ &(m_out.myVehicle.foo));
    pvl->addReference(L"OUT.out.myVehicle.velocity",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"OUT.out.myVehicle.velocity.x",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.velocity.x),
        /*address*/ &(m_out.myVehicle.velocity.x));
    pvl->addVar(L"OUT.out.myVehicle.velocity.y",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.velocity.y),
        /*address*/ &(m_out.myVehicle.velocity.y));
    pvl->addVar(L"OUT.out.myVehicle.velocity.z",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.velocity.z),
        /*address*/ &(m_out.myVehicle.velocity.z));
    pvl->addReference(L"OUT.out.myVehicle.angularVelocity",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"OUT.out.myVehicle.angularVelocity.x",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.angularVelocity.x),
        /*address*/ &(m_out.myVehicle.angularVelocity.x));
    pvl->addVar(L"OUT.out.myVehicle.angularVelocity.y",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.angularVelocity.y),
        /*address*/ &(m_out.myVehicle.angularVelocity.y));
    pvl->addVar(L"OUT.out.myVehicle.angularVelocity.z",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.myVehicle.angularVelocity.z),
        /*address*/ &(m_out.myVehicle.angularVelocity.z));
    pvl->addReference(L"OUT.out.airVehicle",
        /*array*/ L"",
        /*description*/ L"aircraft",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"AirVehicle");
    pvl->addVar(L"OUT.out.airVehicle.foo",
        /*description*/ L"the power of foo",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.foo),
        /*address*/ &(m_out.airVehicle.foo));
    pvl->addReference(L"OUT.out.airVehicle.velocity",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"OUT.out.airVehicle.velocity.x",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.velocity.x),
        /*address*/ &(m_out.airVehicle.velocity.x));
    pvl->addVar(L"OUT.out.airVehicle.velocity.y",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.velocity.y),
        /*address*/ &(m_out.airVehicle.velocity.y));
    pvl->addVar(L"OUT.out.airVehicle.velocity.z",
        /*description*/ L"",
        /*units*/ L"ft/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.velocity.z),
        /*address*/ &(m_out.airVehicle.velocity.z));
    pvl->addReference(L"OUT.out.airVehicle.angularVelocity",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"OUT.out.airVehicle.angularVelocity.x",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.angularVelocity.x),
        /*address*/ &(m_out.airVehicle.angularVelocity.x));
    pvl->addVar(L"OUT.out.airVehicle.angularVelocity.y",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.angularVelocity.y),
        /*address*/ &(m_out.airVehicle.angularVelocity.y));
    pvl->addVar(L"OUT.out.airVehicle.angularVelocity.z",
        /*description*/ L"",
        /*units*/ L"rad/s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.angularVelocity.z),
        /*address*/ &(m_out.airVehicle.angularVelocity.z));
    pvl->addVar(L"OUT.out.airVehicle.airspeed",
        /*description*/ L"",
        /*units*/ L"kts",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.airspeed),
        /*address*/ &(m_out.airVehicle.airspeed));
    pvl->addVar(L"OUT.out.airVehicle.altitude",
        /*description*/ L"",
        /*units*/ L"m",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_out.airVehicle.altitude),
        /*address*/ &(m_out.airVehicle.altitude));
    pvl->addReference(L"INT.firstChild",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Child");
    pvl->addReference(L"INT.firstChild.inp",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildInp");
    pvl->addVar(L"INT.firstChild.inp.x",
        /*description*/ L"child x",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(firstChild.m_inp.x),
        /*address*/ &(firstChild.m_inp.x));
    pvl->addVar(L"INT.firstChild.inp.y",
        /*description*/ L"child y",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(firstChild.m_inp.y),
        /*address*/ &(firstChild.m_inp.y));
    pvl->addReference(L"INT.firstChild.out",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildOut");
    pvl->addVar(L"INT.firstChild.out.y",
        /*description*/ L"child y",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(firstChild.m_out.y),
        /*address*/ &(firstChild.m_out.y));
    pvl->addReference(L"INT.firstChild.x",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildStates");
    pvl->addVar(L"INT.firstChild.x.time",
        /*description*/ L"",
        /*units*/ L"s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(firstChild.m_x.time),
        /*address*/ &(firstChild.m_x.time));
    pvl->addReference(L"INT.secondChild",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Child");
    pvl->addReference(L"INT.secondChild.inp",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildInp");
    pvl->addVar(L"INT.secondChild.inp.x",
        /*description*/ L"child x",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(secondChild.m_inp.x),
        /*address*/ &(secondChild.m_inp.x));
    pvl->addVar(L"INT.secondChild.inp.y",
        /*description*/ L"child y",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(secondChild.m_inp.y),
        /*address*/ &(secondChild.m_inp.y));
    pvl->addReference(L"INT.secondChild.out",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildOut");
    pvl->addVar(L"INT.secondChild.out.y",
        /*description*/ L"child y",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(secondChild.m_out.y),
        /*address*/ &(secondChild.m_out.y));
    pvl->addReference(L"INT.secondChild.x",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"ChildStates");
    pvl->addVar(L"INT.secondChild.x.time",
        /*description*/ L"",
        /*units*/ L"s",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(secondChild.m_x.time),
        /*address*/ &(secondChild.m_x.time));
    if (doAlign)
        pvl_old->alignToList(pvl);
    // pVarList = pvl;
    return true;
}