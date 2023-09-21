cmake_minimum_required(VERSION 3.0.0)
project(example-sandbox VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(example-sandbox
    main.cpp
    Vector3.cpp
    Eom.cpp
    System.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
