add_library(modules import.c symbol_table.c cli.c)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)
