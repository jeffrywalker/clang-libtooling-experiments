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
clang-check -ast-dump test.h -- -std=c++17 -x c++ -Wdocumentation -fparse-all-comments
```


## Usage
To parse cpp files:
```
./comment-parser test.h -- -std=c++17 -x c++
```
