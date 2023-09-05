#pragma once

namespace Foo
{
    // Test Data structure
    struct MyData
    {
        /// description for var1
        /// \units ft and other things
        /// \convention forward
        /// \details detailed content here
        double var1;
        /// description for var2
        /// \note this should be a note
        /// \units rad/s
        /// \convention forward
        double var2;
        /// \units m/s
        double var3;
    };
}  // namespace Foo
