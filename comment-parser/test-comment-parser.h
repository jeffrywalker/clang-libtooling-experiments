#pragma once

namespace Foo
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

    // Test Data structure
    struct MyData
    {
        /// description for var1
        /// \units ft
        /// \convention forward
        /// \range [0, 180]
        /// \details detailed content here
        double var1;
        /// description for var2
        /// \note this should be a note
        /// \units rad/s
        /// \convention +RIGHT
        double var2;
        /// \units m/s
        double var3;

        // \units kg
        /// Note some stuff
        double var4;

        /// \units m
        /// \convention NED
        Vector3 position;
    };
}  // namespace Foo
