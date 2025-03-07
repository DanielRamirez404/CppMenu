cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

message(STATUS "Fetching the CppSafeIO library...")

FetchContent_Declare( cppsafeio 
    GIT_REPOSITORY  https://github.com/DanielRamirez404/CppSafeIO.git 
    GIT_TAG         v2.0.0
    GIT_SHALLOW     TRUE 
)

FetchContent_MakeAvailable(cppsafeio)

if(NOT DEFINED CPP_MENU)
    set(CPP_MENU "CppMenu" CACHE STRING "Name for the CppMenu library")
endif()

add_subdirectory(src)
target_link_libraries(${CPP_MENU} PUBLIC ${CPP_SAFE_IO})
