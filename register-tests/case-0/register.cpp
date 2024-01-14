#include "MyClass.h"
#include <string>
void registerReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName){}
void registerVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* varType, void* address, const wchar_t* enumName = nullptr){}
void MyClass::registerData()
{
registerReference(L"INP.inp", L"", L"system input data", L"", L"", L"", L"", L"Inputs");
registerVar(L"INP.inp.u", L"primary input", L"ft", L"", L"", L"", L"double", &(m_inp.u));
registerVar(L"INP.inp.mode", L"operational mode", L"", L"OFF(0) ON(1) IDLE(2) ", L"", L"", L"(ENUM) Mode", &(m_inp.mode));
registerReference(L"OUT.out", L"", L"system output data", L"", L"", L"", L"", L"Outputs");
registerVar(L"OUT.out.y", L"y output", L"", L"", L"", L"", L"double", &(m_out.y));
registerReference(L"OUT.out.position", L"", L"", L"ft", L"", L"", L"", L"Vec3");
registerVar(L"OUT.out.position.x", L"", L"ft", L"", L"", L"", L"double", &(m_out.position.x));
registerVar(L"OUT.out.position.y", L"", L"ft", L"", L"", L"", L"double", &(m_out.position.y));
registerVar(L"OUT.out.position.z", L"", L"ft", L"", L"", L"", L"double", &(m_out.position.z));
registerReference(L"OUT.out.myVehicle", L"", L"my vehicle", L"", L"", L"", L"", L"Vehicle");
registerVar(L"OUT.out.myVehicle.foo", L"the power of foo", L"", L"", L"", L"", L"int", &(m_out.myVehicle.foo));
registerReference(L"OUT.out.myVehicle.velocity", L"", L"", L"ft/s", L"", L"", L"", L"Vec3");
registerVar(L"OUT.out.myVehicle.velocity.x", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.myVehicle.velocity.x));
registerVar(L"OUT.out.myVehicle.velocity.y", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.myVehicle.velocity.y));
registerVar(L"OUT.out.myVehicle.velocity.z", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.myVehicle.velocity.z));
registerReference(L"OUT.out.myVehicle.angularVelocity", L"", L"", L"rad/s", L"", L"", L"", L"Vec3");
registerVar(L"OUT.out.myVehicle.angularVelocity.x", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.myVehicle.angularVelocity.x));
registerVar(L"OUT.out.myVehicle.angularVelocity.y", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.myVehicle.angularVelocity.y));
registerVar(L"OUT.out.myVehicle.angularVelocity.z", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.myVehicle.angularVelocity.z));
registerReference(L"OUT.out.airVehicle", L"", L"aircraft", L"", L"", L"", L"", L"AirVehicle");
registerVar(L"OUT.out.airVehicle.foo", L"the power of foo", L"", L"", L"", L"", L"int", &(m_out.airVehicle.foo));
registerReference(L"OUT.out.airVehicle.velocity", L"", L"", L"ft/s", L"", L"", L"", L"Vec3");
registerVar(L"OUT.out.airVehicle.velocity.x", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.airVehicle.velocity.x));
registerVar(L"OUT.out.airVehicle.velocity.y", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.airVehicle.velocity.y));
registerVar(L"OUT.out.airVehicle.velocity.z", L"", L"ft/s", L"", L"", L"", L"double", &(m_out.airVehicle.velocity.z));
registerReference(L"OUT.out.airVehicle.angularVelocity", L"", L"", L"rad/s", L"", L"", L"", L"Vec3");
registerVar(L"OUT.out.airVehicle.angularVelocity.x", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.airVehicle.angularVelocity.x));
registerVar(L"OUT.out.airVehicle.angularVelocity.y", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.airVehicle.angularVelocity.y));
registerVar(L"OUT.out.airVehicle.angularVelocity.z", L"", L"rad/s", L"", L"", L"", L"double", &(m_out.airVehicle.angularVelocity.z));
registerVar(L"OUT.out.airVehicle.airspeed", L"", L"kts", L"", L"", L"", L"double", &(m_out.airVehicle.airspeed));
registerVar(L"OUT.out.airVehicle.altitude", L"", L"m", L"", L"", L"", L"double", &(m_out.airVehicle.altitude));

}