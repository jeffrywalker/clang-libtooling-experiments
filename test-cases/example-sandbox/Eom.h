#pragma once
#include "Vector3.h"

namespace eom
{
    class Eom
    {
            public:
        struct States
        {
            Vector3 pos;
            Vector3 vel;
        };

        // explicitly expose things. ANYONE can abuse the access.
        States& getStates();
        States& getStatesPv();
        void step();

            private:
        /// \register getStates
        States mX;
        /// \register getStatesPv
        States mXpv;
        double mFoo = 1.0;
        bool mBaz   = true;
        // hidden value
        States mXhidden;
    };
}  // namespace eom