This extends the baseline `comment-parser` to handle associations of instances.
For example:

```cpp
namespace foo
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
    struct MyData
    {
        /// \units ft/s
        Vector3 velocity;
        /// \units ft/s^2
        Vector3 acceleration;
        /// \units rad/s
        Vector3 angularVelocity;
    };
}
```

Should yield:

```cpp
/// \units ft/s
MyData::velocity::x
/// \units rad/s
MyData::angularVelocity::x
```

To accomplish this it is necessary to mind the relationship between `MyData::velocity` and `Vector3` and the corresponding (unit) definitions.

## Building
**Windows**:
```sh
cmake -B build && cmake --build build --config RelWithDebInfo --target install
```