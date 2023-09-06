This code is from the [clang example](https://clang.llvm.org/docs/RAVFrontendAction.html#how-to-write-recursiveastvisitor-based-astfrontendactions)

## Build
```sh
cmake -B build && cmake --build build --config RelWithDebInfo --target install
```

## Run
```sh
cd ../bin
contents=$(<find-class-decls.h )
./find-class-decls.exe "$contents"
```
**Input**
```cpp
namespace n
{
    namespace m
    {
        class C
        {
        };
    }  // namespace m
}  // namespace n
```

**Output**
```sh
Found declaration at 5:9
```