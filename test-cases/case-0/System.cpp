#include "System.h"
#include <iostream>
#include <typeinfo>

void System::registerData()
{
    // registering requires access to the data memory.
    double* x = &mData.x;
    std::cout << "x: " << *x << "\n";
    *x += 10.0;
    std::cout << "x-mod: " << *x << "\n";
    std::cout << "type: " << typeid(&mData.x).name() << "\n";

    // nested data - still accessible with all public structures
    double* q = &mData.extData.q;
    std::cout << "q: " << *q << "\n";
    *q += 20.0;
    std::cout << "q-mod: " << *q << "\n";
    std::cout << "type: " << typeid(mData.extData.q).name() << "\n";
}