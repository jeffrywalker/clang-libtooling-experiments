"""
Setup utility for cloning, building and configuring LLVM/Clang dependency.

Notes:
------
* LLVM repo, build, install locations should be out-of-tree
* use --writeconfig option to create the default file for modification
* use --clone to obtain the correct LLVM repo
* last use --llvm --clang to compile the dependencies

Reference: https://llvm.org/docs/GettingStarted.html#stand-alone-builds
"""
import os, sys, argparse
import json
from build_utils import *


default_config_filename = "llvm-config.json"
# specify default configuration
default_config = [
    {
        "comment": "type of build to use, Release or RelWithDebInfo",
        "build_type": "RelWithDebInfo",
    },
    {"comment": "number of jobs passed to Ninja -j option", "jobs": 8},
    {
        "comment": "(windows) Visual Studio VC VarsBat to setup toolchain",
        "vcvarsbat": '"C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Auxiliary/Build/vcvars64.bat"',
    },
    {"comment": "build directory for llvm", "llvm_build_dir": "../build-llvm"},
    {"comment": "build directory for clang", "clang_build_dir": "../build-clang"},
    {
        "comment": "directory of the cloned LLVM project: https://github.com/llvm/llvm-project",
        "llvm_repo_dir": "../llvm",
    },
    {
        "comment": "Where llvm/clang should be installed. Also informs binder where LLVM/Clang libraries are.",
        "llvm_install_prefix": "../llvm-reldbg",
    },
    {
        "comment": "LLVM project source that is cloned",
        "llvm_repo": "https://github.com/llvm/llvm-project.git",
        "llvm_branch": "llvmorg-16.0.6",
    },
    {
        "comment": "LLVM options required by binder",
        "llvm_options": "-DLLVM_ENABLE_RTTI=ON -DLLVM_ENABLE_EH=1",
    },
]


def write_default_config():
    """creates the default config file"""
    with open(default_config_filename, "w") as f:
        f.write(json.dumps(default_config, indent=4))


def clone_llvm(
    repo: str = "https://github.com/llvm/llvm-project",
    destination: str = "../llvm",
    branch: str = "llvmorg-16.0.6",
):
    """performs git commands to clone required source"""
    subprocess.run(f"git clone --branch {branch} {repo} {destination}")


def compile_llvm(config: dict):
    """invokes commands to configure and compile LLVM (requires cloned repo)"""
    if not os.path.isdir(config["llvm_build_dir"]):
        os.makedirs(config["llvm_build_dir"])
    setup_cmd = windowsSetupCmdString(config["vcvarsbat"])
    # configure string command
    llvm_str = (
        "{setup} cmake -G Ninja -S {llvm_dir}/llvm -B {build_llvm} "
        + "-DLLVM_INSTALL_UTILS=ON "
        + "-DCMAKE_INSTALL_PREFIX={install_prefix} "
        + "-DCMAKE_BUILD_TYPE={build_type} "
        + "{options}"
    )
    # configure
    execute(
        "Configuring LLVM...",
        llvm_str.format(
            setup=setup_cmd,
            llvm_dir=config["llvm_repo_dir"],
            build_llvm=config["llvm_build_dir"],
            install_prefix=config["llvm_install_prefix"],
            build_type=config["build_type"],
            options=config["llvm_options"],
        ),
    )
    # compile
    execute(
        "Building LLVM...",
        "{setup} ninja -C {build_llvm} {jobs} install".format(
            setup=setup_cmd,
            build_llvm=config["llvm_build_dir"],
            jobs="-j" + str(config["jobs"]),
        ),
    )


def compile_clang(config: dict):
    """invokes configure and compile commands for Clang (requires LLVM build)"""
    if not os.path.isdir(config["clang_build_dir"]):
        os.makedirs(config["clang_build_dir"])
    setup_cmd = windowsSetupCmdString(config["vcvarsbat"])
    clang_str = (
        "{setup} cmake -G Ninja -S {llvm_dir}/clang -B {build_clang} "
        + "-DLLVM_EXTERNAL_LIT={build_llvm}/utils/lit "
        + "-DLLVM_ROOT={install_prefix} "
        + "-DCMAKE_INSTALL_PREFIX={install_prefix} "
        + "-DCMAKE_BUILD_TYPE={build_type} "
        + "{options}"
    )
    execute(
        "Configuring CLANG...",
        clang_str.format(
            setup=setup_cmd,
            llvm_dir=config["llvm_repo_dir"],
            build_clang=config["clang_build_dir"],
            build_llvm=config["llvm_build_dir"],  # may be the install location?
            install_prefix=config["llvm_install_prefix"],
            build_type=config["build_type"],
            options=config["llvm_options"],
        ),
    )
    execute(
        "Building CLANG...",
        "{setup} ninja -C {build_clang} {jobs} install ".format(
            setup=setup_cmd,
            build_clang=config["clang_build_dir"],
            jobs="-j" + str(config["jobs"]),
        ),
    )


def main(argv):
    """main entry point function"""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--writeconfig",
        action="store_true",
        help="write the default configuration file",
    )
    parser.add_argument(
        "--config",
        default=default_config_filename,
        type=str,
        help="configuration file to read for build instructions (--writeconfig to create default)",
    )
    parser.add_argument("--clone", action="store_true", help="clones the LLVM project")
    parser.add_argument(
        "--llvm",
        action="store_true",
        help="compiles LLVM using prescribed configuration",
    )
    parser.add_argument(
        "--clang",
        action="store_true",
        help="compiles Clang using prescribed configuration",
    )
    args = parser.parse_args(argv)

    config = configFromArray(default_config)
    # no commands provided
    if not argv:
        parser.print_help()
        return

    if args.writeconfig:
        write_default_config()
        return

    if args.config:
        if (args.config == default_config_filename) and not os.path.isfile(
            default_config_filename
        ):
            write_default_config()
        with open(args.config) as js_file:
            config_array = json.loads(js_file.read())
        # collapse the verbose config array (ignore comment entries)
        config = configFromArray(configArray=config_array, defaultConfig=config)

    if args.clone:
        clone_llvm(
            repo=config["llvm_repo"],
            destination=config["llvm_repo_dir"],
            branch=config["llvm_branch"],
        )

    if args.llvm:
        # compile llvm
        compile_llvm(config=config)
    if args.clang:
        # compile clang
        compile_clang(config=config)


if "__main__" == __name__:
    main(argv=sys.argv[1:])
