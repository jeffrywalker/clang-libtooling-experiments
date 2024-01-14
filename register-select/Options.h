#pragma once

#include "llvm/Config/llvm-config.h"
#include "llvm/Support/CommandLine.h"

extern llvm::cl::OptionCategory DataRegisterToolCategory;

/// items to be registered
extern llvm::cl::list<std::string> O_register;
/// configuration file to be read
extern llvm::cl::opt<std::string> O_config;
/// suppress output errors (clang/llvm)
extern llvm::cl::opt<bool> O_suppress_errors;

/// logging level
extern llvm::cl::opt<std::string> O_log_level;

/// output file
extern llvm::cl::opt<std::string> O_output_file;

/// output directory
extern llvm::cl::opt<std::string> O_output_dir;

/// include header in output file
extern llvm::cl::opt<std::string> O_output_include;