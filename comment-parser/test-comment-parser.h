#pragma once

namespace Foo
{
    struct Vector3
    {
        double x;
        double y;
        double z;
    };

    // Test Data structure
    struct MyData
    {
        /// description for var1
        /// \units ft and other things
        //
        /// \convention forward
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
