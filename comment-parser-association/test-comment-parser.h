#pragma once

namespace Foo
{
    struct Vector3
    {
        /// the x var description
        /// \units inherit
        double x;
        /// the y var description
        /// \units inherit
        double y;
        /// The z variable description
        /// \units inherit
        double z;
    };

    enum class SpeedType
    {
        GROUND = 0,
        AIR,
        RELATIVE
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
        /// \units Hz
        /// \description var3 is meaningful
        int var3;
        /// the speed type enumaration usage
        SpeedType speedType;
        /// an unsigned int
        unsigned int frameCount;

        /// Note some stuff
        /// \convention TRUE if valid
        bool isValid;

        /// \units m
        /// \convention NED
        /// \description position of something
        Vector3 position;
    };
}  // namespace Foo
