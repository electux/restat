#
# @brief   restatdesk_tests list of all sources and unit tests for config
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    RESTAT_COM_HEADERS
    ${PROJECT_SOURCE_DIR}/../restatdesk/
)

set(
    RESTAT_COM_SOURCES
    ${PROJECT_SOURCE_DIR}/../restatdesk/com/serial/serial_com.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/com/serial/serialw/serial_lib_wrapper.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/com/serial/serial_utils.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/com/ble/configurator/ble_com_configurator.cc
)

set(
    RESTAT_COM_TESTS
    ${PROJECT_SOURCE_DIR}/com/test_serial_baude_rate.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_data_bits.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_parity.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_stop_bits.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_flow_control.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_setup.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_open.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_close.cc
    ${PROJECT_SOURCE_DIR}/com/test_serial_read.cc
    ${PROJECT_SOURCE_DIR}/com/test_ble_com.cc
    #${PROJECT_SOURCE_DIR}/com/test_serial_write.cc
)
