cmake_minimum_required(VERSION 3.10)
# use the directory name as the project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/..")
include(CTest)
enable_testing()

# lazily grab all sources
file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/*.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# install command

install(TARGETS ${PROJECT_NAME} DESTINATION)
