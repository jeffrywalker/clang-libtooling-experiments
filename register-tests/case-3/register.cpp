#include "ClassBaseData.h"
#include <string>
#include <vector>
#include <utility>
void registerReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName){}
void registerVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* varType, void* address, const wchar_t* enumName = nullptr){}
void Vehicles::registerData()
{
registerReference(L"INP.ship", L"", L"", L"", L"", L"", L"", L"Ship");
registerVar(L"INP.ship.u", L"", L"", L"", L"", L"", L"double", &(ship.u));
registerVar(L"INP.ship.x", L"", L"", L"", L"", L"", L"double", &(ship.x));
registerVar(L"INP.ship.count", L"", L"", L"", L"", L"", L"int", &(ship.count));
registerReference(L"INP.ship.leftNode", L"", L"", L"", L"", L"", L"", L"DataNode");
registerVar(L"INP.ship.leftNode.foo", L"", L"", L"", L"", L"", L"int", &(ship.leftNode.foo));
registerVar(L"INP.ship.leftNode.baz", L"", L"", L"", L"", L"", L"double", &(ship.leftNode.baz));
registerReference(L"INP.ship.rightNode", L"", L"", L"", L"", L"", L"", L"DataNode");
registerVar(L"INP.ship.rightNode.foo", L"", L"", L"", L"", L"", L"int", &(ship.rightNode.foo));
registerVar(L"INP.ship.rightNode.baz", L"", L"", L"", L"", L"", L"double", &(ship.rightNode.baz));
registerVar(L"INP.ship.cruiseSpeed", L"", L"kts", L"", L"", L"", L"double", &(ship.cruiseSpeed));
registerVar(L"INP.ship.heading", L"", L"deg", L"[0, 360]", L"", L"", L"double", &(ship.heading));
registerReference(L"INP.aircraft", L"", L"", L"", L"", L"", L"", L"Aircraft");
registerVar(L"INP.aircraft.u", L"", L"", L"", L"", L"", L"double", &(aircraft.u));
registerVar(L"INP.aircraft.x", L"", L"", L"", L"", L"", L"double", &(aircraft.x));
registerVar(L"INP.aircraft.count", L"", L"", L"", L"", L"", L"int", &(aircraft.count));

}