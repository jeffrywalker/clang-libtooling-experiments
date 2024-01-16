#include "MyClass.h"
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


bool MyClass::registerData(const std::wstring& listName, IVarData* pVarData)
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
    pvl->addReference(L"INP.inp.pass",
        /*array*/ L"",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*structName*/ L"Vec3");
    pvl->addVar(L"INP.inp.pass.x",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_inp.pass.x),
        /*address*/ &(m_inp.pass.x));
    pvl->addVar(L"INP.inp.pass.y",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_inp.pass.y),
        /*address*/ &(m_inp.pass.y));
    pvl->addVar(L"INP.inp.pass.z",
        /*description*/ L"",
        /*units*/ L"",
        /*convention*/ L"",
        /*default*/ L"",
        /*range*/ L"",
        /*varType*/ IVarDef::getVarType(m_inp.pass.z),
        /*address*/ &(m_inp.pass.z));
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
    if (doAlign)
        pvl_old->alignToList(pvl);
    // pVarList = pvl;
    return true;
}