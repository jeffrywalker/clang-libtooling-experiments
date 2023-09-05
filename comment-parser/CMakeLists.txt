# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project
cmake_minimum_required(VERSION 3.20)
project("comment-parser")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/..")

# LLVM
set(LLVM_DIR ${CMAKE_CURRENT_LIST_DIR}/../../llvm-release/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Clang
set(Clang_DIR ${CMAKE_CURRENT_LIST_DIR}/../../llvm-release/lib/cmake/clang)
find_package(Clang REQUIRED)
message(STATUS "Found Clang")
message(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/CommentParser.cpp
)

# Now build our tools
add_executable(${PROJECT_NAME} ${SOURCES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support
)

# Link against LLVM libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs}
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangSerialization
    clangTooling
)

install(TARGETS ${PROJECT_NAME} DESTINATION)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_LIST_DIR}/test-comment-parser.h"
    "${CMAKE_CURRENT_LIST_DIR}/../bin/test-comment-parser.h"
)