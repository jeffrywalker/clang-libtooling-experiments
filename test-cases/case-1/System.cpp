#include "System.h"
#include <iostream>
#include <typeinfo>

System::System()
{
    zeroData();
}
void System::zeroData()
{
    foo::Data* _data = this;
    memset(_data, 0, sizeof(foo::Data));
}

void System::registerData()
{
    // registering requires access to the data memory.
    double* _x = &x;
    std::cout << "x: " << *_x << "\n";
    *_x += 10.0;
    std::cout << "x-mod: " << *_x << "\n";
    std::cout << "type: " << typeid(&_x).name() << "\n";

    // nested data - still accessible with all public structures
    double* q = &extData.q;
    std::cout << "q: " << *q << "\n";
    *q += 20.0;
    std::cout << "q-mod: " << *q << "\n";
    std::cout << "type: " << typeid(extData.q).name() << "\n";
}