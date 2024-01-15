#include "ClassBaseData.h"
#include <string>
#include <vector>
#include <utility>
void registerReference(const wchar_t* name, const wchar_t* arrayDesignation, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* structName){}
void registerVar(const wchar_t* name, const wchar_t* description, const wchar_t* units, const wchar_t* convention, const wchar_t* defaultValue, const wchar_t* range, const wchar_t* varType, void* address, const wchar_t* enumName = nullptr){}
void Ship::registerData()
{
registerVar(L"INP.u", L"", L"", L"", L"", L"", L"double", &(u));
registerVar(L"OUT.x", L"", L"", L"", L"", L"", L"double", &(x));
registerVar(L"INT.count", L"", L"", L"", L"", L"", L"int", &(count));
registerReference(L"INT.leftNode", L"", L"", L"", L"", L"", L"", L"DataNode");
registerVar(L"INT.leftNode.foo", L"", L"", L"", L"", L"", L"int", &(leftNode.foo));
registerVar(L"INT.leftNode.baz", L"", L"", L"", L"", L"", L"double", &(leftNode.baz));
registerReference(L"INT.rightNode", L"", L"", L"", L"", L"", L"", L"DataNode");
registerVar(L"INT.rightNode.foo", L"", L"", L"", L"", L"", L"int", &(rightNode.foo));
registerVar(L"INT.rightNode.baz", L"", L"", L"", L"", L"", L"double", &(rightNode.baz));

}