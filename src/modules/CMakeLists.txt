add_library(modules import.c)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)
