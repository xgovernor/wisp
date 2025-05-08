cmake_minimum_required(VERSION 3.10)

project(Wisp)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)


# Add subdirectories for each module
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/codegen)
add_subdirectory(src/runtime)
add_subdirectory(src/modules)

# Main executable
add_executable(wisp src/main.c src/wisp.c)

# Link all modules (order may matter if there are dependencies)
target_link_libraries(wisp
    lexer
    parser
    codegen
    runtime
    modules
)

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
