#include "Options.h"
#include <llvm/Support/CommandLine.h>

using namespace llvm;

llvm::cl::OptionCategory DataRegisterToolCategory("DataRegister options");

cl::list<std::string> O_register("register", cl::desc("Entry point items to register"), cl::cat(DataRegisterToolCategory));

cl::opt<std::string> O_config("config", cl::desc("Specify config file from which bindings setting will be read"), cl::init(""),
                              cl::cat(DataRegisterToolCategory));

cl::opt<bool> O_suppress_errors("suppress-errors", cl::desc("Suppres all the compilers errors."), cl::init(true),
                                cl::cat(DataRegisterToolCategory));

cl::opt<std::string> O_log_level("log-level", cl::desc("Program logging level: DEBUG, INFO, WARNING, ERROR"),
                                 cl::cat(DataRegisterToolCategory), cl::init("INFO"));

cl::opt<std::string> O_output_file("output-file", cl::desc("Output file registration is written to"),
                                   cl::cat(DataRegisterToolCategory), cl::init("register.cpp"));

cl::opt<std::string> O_output_dir("output-dir", cl::desc("Output file directory"), cl::cat(DataRegisterToolCategory), cl::init(""));

cl::opt<std::string> O_output_include("output-include", cl::desc("Output file directory"), cl::cat(DataRegisterToolCategory),
                                      cl::init(""));
