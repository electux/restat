cmake_minimum_required(VERSION 3.12)
project(restat_base_tests C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

# 1. Include Mocks first so that standard Pico and device includes are intercepted
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
    ${CMAKE_CURRENT_SOURCE_DIR}/../restat_base/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../restat_base/src/command
)

# 2. Add Googletest subdirectory from restatdesk_tests (offline/local reuse)
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../restatdesk_tests/googletest
    ${CMAKE_CURRENT_BINARY_DIR}/googletest_build
)

# Include Googletest headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../restatdesk_tests/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../restatdesk_tests/googletest/googlemock/include
)

# 3. Create test executable compiling base C modules with host mock structures
add_executable(
    restat_base_tests
    main.cc
    mocks/mocks.cc
    ../restat_base/src/command/parser.c
    ../restat_base/src/command/command_tbl.c
    tests/test_parser.cc
    tests/test_command.cc
)

# 4. Link GoogleTest libraries
target_link_libraries(
    restat_base_tests
    PUBLIC
    gtest
    gtest_main
    gmock
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(restat_base_tests)
