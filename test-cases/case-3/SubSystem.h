#pragma once
#include "Vector3.h"
#include "ExtTypes.h"

class SubSystem : private foo::States // <- target
{
        public:
    SubSystem();
    struct SubData
    {
        double apple;
        Vector3 velocity; // <- target
    };

    /// \register subData
    SubData* _data();

    /// \register states
    foo::States* _states();

        private:
    SubData mData = {0};
};