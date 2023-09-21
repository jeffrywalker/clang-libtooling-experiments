#include "System.h"
#include <iostream>
#include <typeinfo>

void System::registerData()
{
    // registering requires access to the data memory.

    // register subsystem data, which is private
    double* _x = mSubSystem._data()->velocity._px();
    std::cout << "x: " << *_x << "\n";
    *_x += 10.0;
    std::cout << "x-mod: " << *_x << "\n";
    std::cout << "type: " << typeid(_x).name() << "\n";

    // access to subsys states
    _x = mSubSystem._states()->posNed._px();
    std::cout << "px: " << *_x << "\n";
    *_x += 20.0;
    std::cout << "px-mod: " << *_x << "\n";
    std::cout << "type: " << typeid(_x).name() << "\n";
}