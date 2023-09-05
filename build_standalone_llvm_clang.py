#!/usr/bin/env python

from jsmin import jsmin # allow use of comments
import json
import os, sys, argparse

from build_utils import *

def main(args):
    '''
    This will setup and invoke the build process to support standalone builds.
    Reference: https://llvm.org/docs/GettingStarted.html#stand-alone-builds
    '''
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-c", "--config",
        default="./llvm-build-config.jsonc",
        type=str,
        help="configuration file to read for build instructions"
    )

    options = parser.parse_args()
    # read the json configuration file
    if ".jsonc" in options.config:
        with open(options.config) as js_file:
            minified = jsmin(js_file.read())
        config = json.loads(minified)
    else:
        with open(options.config) as js_file:
            config = json.load(js_file)

    # build dirs
    if not os.path.isdir(config['build_llvm']):
        os.makedirs(config['build_llvm'])
    if not os.path.isdir(config['build_clang']):
        os.makedirs(config['build_clang'])

    # build LLVM
    setupCmd = windowsSetupCmdString(config['vcvarsbat'])
    # options from binder
    llvmOptions = "-DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=1"
    # LLVM
    '''
    llvmStr = "{setup} cmake -G Ninja -S {llvm_dir}/llvm -B {build_llvm} " + \
        "-DLLVM_INSTALL_UTILS=ON " + \
        "-DCMAKE_INSTALL_PREFIX={install_prefix} " + \
        "-DCMAKE_BUILD_TYPE={build_type} " + \
        "{options}"
    execute('Configuring LLVM...',
        llvmStr.format(
            setup=setupCmd,
            llvm_dir=config['llvm_dir'],
            build_llvm=config['build_llvm'],
            install_prefix=config['install_prefix'],
            build_type=config['build_type'],
            options=llvmOptions
            )
        )
    execute('Building LLVM...',
        "{setup} ninja -C {build_llvm} {jobs} install".format(
            setup=setupCmd,
            build_llvm=config['build_llvm'],
            jobs="-j" + str(config['jobs'])
        ))
    '''
    # CLANG
    clangStr = \
        "{setup} cmake -G Ninja -S {llvm_dir}/clang -B {build_clang} " + \
        "-DLLVM_EXTERNAL_LIT={build_llvm}/utils/lit " + \
        "-DLLVM_ROOT={install_prefix} " + \
        "-DCMAKE_INSTALL_PREFIX={install_prefix} " + \
        "-DCMAKE_BUILD_TYPE={build_type} " + \
        "{options}"
    execute("Configuring CLANG...",
        clangStr.format(
            setup=setupCmd,
            llvm_dir=config['llvm_dir'],
            build_clang=config['build_clang'],
            build_llvm=config['build_llvm'], # may be the install location?
            install_prefix=config['install_prefix'],
            build_type=config['build_type'],
            options=llvmOptions
        ))
    execute('Building CLANG...',
        "{setup} ninja -C {build_clang} {jobs} install ".format(
            setup=setupCmd,
            build_clang=config['build_clang'],
            jobs="-j" + str(config['jobs'])
        ))

if __name__ == "__main__":
    main(sys.argv)