The intent is to learn how to parse comments to extract relevant information
used in additional processing.

## Building
**Windows**:
```sh
cmake -B build && cmake --build build --config RelWithDebInfo --target install
```

## Baseline
Using pre-built clang assess the AST:
```
clang-check -ast-dump test-comment-parser.h -- -std=c++17 -x c++ -Wdocumentation -fparse-all-comments
```

Note the `-fparse-all-comments` option will will result in non-Doxygen style comments getting parsed.

## Usage
To parse cpp files:
```
./comment-parser test-comment-parser.h -- -std=c++17 -x c++
```

**Example Input**
```cpp
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

```

**Example Output**
```sh
$ ./comment-parser test-comment-parser.h -- -std=c++17 -x c++ -fparse-all-comments
D:\github\clang-libtooling-experiments\bin\test-comment-parser.h:1:9: warning: #pragma once in main file [-Wpragma-once-outside-header]
#pragma once
        ^

======== FieldDecl found ======
found 'Foo::Vector3::x x' in 'Vector3' is BuiltinType = 1


======== FieldDecl found ======
found 'Foo::Vector3::y y' in 'Vector3' is BuiltinType = 1


======== FieldDecl found ======
found 'Foo::Vector3::z z' in 'Vector3' is BuiltinType = 1


======== FieldDecl found ======
found 'Foo::MyData::var1 var1' in 'MyData' is BuiltinType = 1

units =  ft and other things
convention =  forward

======== FieldDecl found ======
found 'Foo::MyData::var2 var2' in 'MyData' is BuiltinType = 1

units =  rad/s
convention =  +RIGHT

======== FieldDecl found ======
found 'Foo::MyData::var3 var3' in 'MyData' is BuiltinType = 1

units =  m/s

======== FieldDecl found ======
found 'Foo::MyData::var4 var4' in 'MyData' is BuiltinType = 1

units =  kg

======== FieldDecl found ======
found 'Foo::MyData::position position' in 'MyData' is BuiltinType = 0

units =  m
convention =  NED
```