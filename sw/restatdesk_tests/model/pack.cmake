#
# @brief   restatdesk_tests list of all sources and unit tests for model
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    RESTAT_MODEL_HEADERS
    ${PROJECT_SOURCE_DIR}/../restatdesk/
)

set(
    RESTAT_MODEL_SOURCES
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/model.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/model_factory.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/delegate/control/control_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/delegate/serial/serial_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/delegate/general/general_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/delegate/ble/ble_model_delegate.cc
    ${PROJECT_SOURCE_DIR}/../restatdesk/model/delegate/log/log_model_delegate.cc
)

set(
    RESTAT_MODEL_TESTS
    ${PROJECT_SOURCE_DIR}/model/test_model.cc
)
