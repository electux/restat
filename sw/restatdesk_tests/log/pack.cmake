#
# @brief   restatdesk_tests list of all sources and unit tests for log
# @version v1.0.3
# @date    Tue Sep 19 08:55:54 PM CEST 2023
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

set(
    RESTAT_LOG_HEADERS
    ${PROJECT_SOURCE_DIR}/../restatdesk/
)

set(
    RESTAT_LOG_SOURCES
    ${PROJECT_SOURCE_DIR}/../restatdesk/log/log.cc
)

set(
    RESTAT_LOG_TESTS
    ${PROJECT_SOURCE_DIR}/log/test_log_file_path.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_log_level.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_open.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_message_format.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_closed_stream.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_filtering.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_multi_thread.cc
    ${PROJECT_SOURCE_DIR}/log/test_log_close.cc
    ${PROJECT_SOURCE_DIR}/log/test_mock_log_failure.cc
)
