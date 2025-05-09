add_library(utils utils.c error.c intern.c)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include ../symbol_table)
