#!/usr/bin/env python

import subprocess
import sys, time
from enum import Enum


def configFromArray(configArray: list[dict], defaultConfig: dict = {}) -> dict:
    """collapses list of options to single dictionary"""
    config = defaultConfig.copy()
    for d in configArray:
        for k, v in d.items():
            if k != "comment":
                config[k] = v
    return config


class PlatformType(Enum):
    LINUX = 0
    WINDOWS = 1
    UNSUPPORTED = -1


def getPlatformType():
    if sys.platform.startswith("linux"):
        return PlatformType.LINUX
    elif sys.platform == "win32":
        return PlatformType.WINDOWS
    else:
        return PlatformType.UNSUPPORTED


def windowsSetupCmdString(batfile: str) -> str:
    """
    command string for windows developer.
    non-windows platform returns "".
    """
    if getPlatformType() == PlatformType.WINDOWS:
        return "{vcvars} && set CC=cl && set CXX=cl && ".format(vcvars=batfile)
    else:
        return ""


def execute(
    message,
    command_line,
    return_="status",
    until_successes=False,
    terminate_on_failure=True,
    silent=False,
    silence_output=False,
):
    if not silent:
        print(message)
        print(command_line)
        sys.stdout.flush()
    while True:
        p = subprocess.Popen(
            command_line,
            bufsize=0,
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        )
        output, errors = p.communicate()

        output = output + errors

        output = output.decode(encoding="utf-8", errors="replace")

        exit_code = p.returncode

        if exit_code or not (silent or silence_output):
            print(output)
            sys.stdout.flush()

        if exit_code and until_successes:
            pass  # Thats right - redability COUNT!
        else:
            break

        print("Error while executing {}: {}\n".format(message, output))
        print("Sleeping 60s... then I will retry...")
        sys.stdout.flush()
        time.sleep(60)

    if return_ == "tuple":
        return (exit_code, output)

    if exit_code and terminate_on_failure:
        print("\nEncounter error while executing: " + command_line)
        if return_ == True:
            return True
        else:
            print("\nEncounter error while executing: " + command_line + "\n" + output)
            sys.exit(1)

    if return_ == "output":
        return output
    else:
        return False


if __name__ == "__main__":
    print("this module is not intended to run as a script")
