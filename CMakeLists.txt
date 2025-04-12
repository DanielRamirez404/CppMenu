cmake_minimum_required(VERSION 3.14)
if(NOT DEFINED CPP_MENU)
    set(CPP_MENU "CppMenu" CACHE STRING "Name for the CppMenu library")
endif()

project(CPP_MENU)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()
include(FetchContent)

message(STATUS "Fetching the CppSafeIO library...")

FetchContent_Declare( cppsafeio 
    GIT_REPOSITORY  https://github.com/DanielRamirez404/CppSafeIO.git 
    GIT_TAG         v2.1.1
    GIT_SHALLOW     TRUE 
)

FetchContent_MakeAvailable(cppsafeio)

add_subdirectory(src)
add_subdirectory(tests)
