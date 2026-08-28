#
# @brief   restatdesk_tests main entry point for build tests
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

cmake_minimum_required(VERSION 3.12)
project(restat_tests CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GOOGLETEST_VERSION 1.14.0)

enable_testing()

# Add gtkmm and glibmm packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0 glibmm-2.4)


# Add sources and includes for googletest
add_subdirectory(googletest)
include_directories(googletest/include)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

# Add sources and includes
include(${PROJECT_SOURCE_DIR}/com/pack.cmake)
include(${PROJECT_SOURCE_DIR}/config/pack.cmake)
include(${PROJECT_SOURCE_DIR}/log/pack.cmake)
include(${PROJECT_SOURCE_DIR}/channel/pack.cmake)
include(${PROJECT_SOURCE_DIR}/model/pack.cmake)
include_directories(com)
include_directories(config)
include_directories(log)
include_directories(channel)
include_directories(model)
include_directories(${RESTAT_COM_HEADERS})
include_directories(${RESTAT_CONFIG_HEADERS})
include_directories(${RESTAT_LOG_HEADERS})
include_directories(${RESTAT_PARAMS_HEADERS})
include_directories(${RESTAT_MODEL_HEADERS})

add_executable(
    restat_tests
    main.cc
    ${RESTAT_COM_TESTS}
    ${RESTAT_CONFIG_TESTS}
    ${RESTAT_LOG_TESTS}
    ${RESTAT_MODEL_TESTS}
    ${RESTAT_COM_SOURCES}
    ${RESTAT_CONFIG_SOURCES}
    ${RESTAT_LOG_SOURCES}
    ${RESTAT_MODEL_SOURCES}
    ${RESTAT_PARAMS_TESTS}
)

# Link libraries
target_link_libraries(
    restat_tests
    PUBLIC
    gtest
    gtest_main
    gmock
    gmock_main
    PkgConfig::gtkmm
)
include(GoogleTest)
gtest_discover_tests(restat_tests)
