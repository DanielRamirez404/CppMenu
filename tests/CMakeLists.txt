cmake_minimum_required(VERSION 3.14)
project(Tests LANGUAGES CXX)

add_executable(Tests tests.cpp)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
add_subdirectory(${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

target_link_libraries(Tests ${CPP_MENU})
