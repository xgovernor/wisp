cmake_minimum_required(VERSION 3.10)

project(Wisp)

# Enable strict compiler warnings and treat warnings as errors
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -Werror)

include_directories(src/include)

# Add subdirectories for each module
add_subdirectory(src/utils)
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/codegen)
add_subdirectory(src/runtime)
add_subdirectory(src/modules)

# Main executable
add_executable(wisp src/main.c src/wisp.c src/modules/interpreter.c)

# Link all modules (order may matter if there are dependencies)
target_link_libraries(wisp
    lexer
    parser
    codegen
    runtime
    modules
    utils
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

# Install rules for CMake (for packaging and system install)
install(TARGETS wisp
    RUNTIME DESTINATION bin
)
install(DIRECTORY src/include/ DESTINATION include/wisp FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/lexer/ DESTINATION include/wisp/lexer FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/parser/ DESTINATION include/wisp/parser FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/codegen/ DESTINATION include/wisp/codegen FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/runtime/ DESTINATION include/wisp/runtime FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/modules/ DESTINATION include/wisp/modules FILES_MATCHING PATTERN "*.h")
install(DIRECTORY src/utils/ DESTINATION include/wisp/utils FILES_MATCHING PATTERN "*.h")

# Optionally install documentation (Doxygen HTML)
install(DIRECTORY docs/doxygen/html/ DESTINATION share/doc/wisp/html OPTIONAL)

# Custom target to build a .deb package using the packaging/install.sh script
add_custom_target(deb
    COMMAND bash ${CMAKE_SOURCE_DIR}/packaging/install.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Build Debian .deb package using packaging/install.sh"
)

# === Tests ===
# Add test executables
add_executable(arena_test tests/arena_test.c)
add_executable(error_tester tests/error_tester.c)
add_executable(fuzz_lexer tests/fuzz_lexer.c)
add_executable(fuzz_parser tests/fuzz_parser.c)

# Link test executables with the same libraries as main if needed
# (Assume all modules/utils may be needed for linking)
target_link_libraries(arena_test utils)
target_link_libraries(error_tester modules utils)
target_link_libraries(fuzz_lexer lexer utils)
target_link_libraries(fuzz_parser lexer parser utils)

# Register tests with CTest
add_test(NAME arena_test COMMAND arena_test)
add_test(NAME error_tester COMMAND error_tester)
add_test(NAME fuzz_lexer COMMAND fuzz_lexer)
add_test(NAME fuzz_parser COMMAND fuzz_parser)
