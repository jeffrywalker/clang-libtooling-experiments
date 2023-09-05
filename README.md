# clang-libtooling-experiments
Experiments developing tools using Clang LibTooling.

* Using [llvmorg-16.0.6](https://github.com/llvm/llvm-project/tree/llvmorg-16.0.6)

## Standalone Build
LLVM/CLANG takes forever to build. To expedite development on tools a standalone build is established following [docs](https://llvm.org/docs/GettingStarted.html#stand-alone-builds).
This step is carried out by `build_standalone_llvm_clang.py`[^1] which loads configurations from `llvm-build-config.jsonc`[^2].

[^1]: Python was used to control the build process for ease in cross-platform support.
[^2]: JSON configuration file is used to avoid hard-coding settings and lengthy command line options.

The assumed default directory structure is as follows:
```
<root>
+---llvm
+---clang-libtooling-experiments
|   +---build_standalone_llvm_clang.py
|   \---example
+---build-llvm
+---build-clang
+---llvm-release
```
