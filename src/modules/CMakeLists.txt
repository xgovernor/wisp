add_library(modules import.c symbol_table.c cli.c logger.c interpreter.c)
target_link_libraries(modules PUBLIC lexer)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)
