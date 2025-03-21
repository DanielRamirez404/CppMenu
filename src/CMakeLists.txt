add_library(${CPP_MENU} STATIC cppmenu.cpp)
target_include_directories(${CPP_MENU} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${CPP_MENU} PUBLIC ${CPP_SAFE_IO})
