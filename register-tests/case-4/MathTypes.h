#pragma once

/// template base data class
template <class Inputs, class Outputs, class Internals> class DataBase : public Inputs, public Outputs, public Internals
{
};

namespace math
{
    struct Vector3
    {
        /// \units inherit
        double x;
        /// \units inherit
        double y;
        /// \units inherit
        double z;
    };
}  // namespace math