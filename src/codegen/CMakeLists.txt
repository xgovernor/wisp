add_library(codegen codegen.c)
target_include_directories(codegen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../include)
