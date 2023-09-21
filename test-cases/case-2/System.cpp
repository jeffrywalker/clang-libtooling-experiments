#include "System.h"
#include <iostream>
#include <typeinfo>

void System::registerData()
{
    // registering requires access to the data memory.
    double* _x = mData.position._px();
    std::cout << "x: " << *_x << "\n";
    *_x += 10.0;
    std::cout << "x-mod: " << *_x << "\n";
    std::cout << "type: " << typeid(_x).name() << "\n";
}