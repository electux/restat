#
# @brief   restatdesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    RESTAT_CONFIG_HEADERS
    ${PROJECT_SOURCE_DIR}/../restatdesk/
)

set(
    RESTAT_CONFIG_SOURCES
    ${PROJECT_SOURCE_DIR}/../restatdesk/config/config_manager.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/config/config_manager_utils.cc
)

set(
    RESTAT_CONFIG_TESTS
    ${PROJECT_SOURCE_DIR}/config/test_config_control.cc
    ${PROJECT_SOURCE_DIR}/config/test_config_log.cc
    ${PROJECT_SOURCE_DIR}/config/test_config_serial.cc
    ${PROJECT_SOURCE_DIR}/config/test_config_load.cc
    ${PROJECT_SOURCE_DIR}/config/test_config_store.cc
)
