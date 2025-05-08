add_library(runtime runtime.c)
target_include_directories(runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)
