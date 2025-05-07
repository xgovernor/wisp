cmake_minimum_required(VERSION 3.10)

project(Wisp)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

file(GLOB SOURCES
    src/lexer.c
    src/parser.c
    src/codegen.c
    src/main.c
)

add_executable(wisp ${SOURCES})

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(LLVM_LINK_COMPONENTS
    core
    executionengine
    irreader
    native
    support
)

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})
target_link_libraries(wisp ${llvm_libs})
