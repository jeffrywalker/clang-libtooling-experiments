This example follows the [loop-convert tutorial](https://clang.llvm.org/docs/LibASTMatchersTutorial.html#step-1-create-a-clangtool) with modifications to support a standalone build.

## Prerequisites
* LLVM/CLANG have been built and installed to support standalone. i.e., `python build_standalone_llvm_clang.py`

## Building

```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=..
cmake --build build --config RelWithDebInfo --target install
```