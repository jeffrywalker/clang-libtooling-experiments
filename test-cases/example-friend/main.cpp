#include "System.h"
#include <iostream>

int main(int, char**)
{
    std::cout << "Hello, from example-sandbox!\n";

    System system;
    std::cout << "pos-x: " << system.getEom().getStates().pos.x() << "\n";
    system.getEom().getStates().pos.x(10.0);

    *system.getEom().getStates().pos.px() += 5.0;

    std::cout << "pos-x: " << system.getEom().getStates().pos.x() << "\n";
}
