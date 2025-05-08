cmake_minimum_required(VERSION 3.10)

project(Wisp)

set(CMAKE_C_STANDARD 11)

include_directories(src/include)

# Add subdirectories for new modules
add_subdirectory(src/utils)
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
