cmake_minimum_required(VERSION 3.14)
include(CTest)

add_executable(CppMenu-AutomatedTests automated-tests.cpp)
target_link_libraries(CppMenu-AutomatedTests ${CPP_MENU})
add_test(NAME CppMenu-Testing COMMAND CppMenu-AutomatedTests)

add_executable(CppMenu-Tests tests.cpp testfunctions.cpp)
target_link_libraries(CppMenu-Tests ${CPP_MENU})
target_include_directories(CppMenu-Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
