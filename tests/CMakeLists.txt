cmake_minimum_required(VERSION 3.14)
project(Tests LANGUAGES CXX)

add_executable(Tests tests.cpp testfunctions.cpp)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
add_subdirectory(${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

target_include_directories(Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Tests ${CPP_MENU})
