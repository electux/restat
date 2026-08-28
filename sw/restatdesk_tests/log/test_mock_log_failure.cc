////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_log_failure.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// restatdesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// restatdesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "mock_log.h"
#include <gtest/gtest.h>

using namespace Electux::App::Logger;
using ::testing::Return;
using ::testing::_;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief A hypothetical component that relies on ILog.
///
/// This class is used to demonstrate how to test interaction with the Logger interface
/// using a mock object, specifically for error handling scenarios.
////////////////////////////////////////////////////////////////////////////////////////////////////////
class LogConsumer
{
public:
    explicit LogConsumer(ILog& logger) : m_logger(logger) {}

    bool doCriticalWork()
    {
        // Attempt to open the logger
        if (!m_logger.open())
        {
            // Unhappy flow: Logger failed to open
            return false;
        }

        m_logger.log("Critical work started", LogLevel::Info);
        // ... do work ...
        m_logger.close();

        return true;
    }

private:
    ILog& m_logger;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the unhappy flow where the logger fails to open.
///
/// Verifies that the consumer handles the failure gracefully and does not attempt
/// to log messages if the logger cannot be opened.
///
/// @param MockLogTest The test fixture.
/// @param OpenFailureHandlingTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockLogTest, OpenFailureHandlingTest)
{
    MockLog mockLogger;
    LogConsumer consumer(mockLogger);

    // Expectation: open() is called and returns false (simulating failure)
    EXPECT_CALL(mockLogger, open()).WillOnce(Return(false));

    // Expectation: log() should NOT be called because open() failed
    EXPECT_CALL(mockLogger, log(_, _)).Times(0);

    // Expectation: close() should NOT be called
    EXPECT_CALL(mockLogger, close()).Times(0);

    // Verify the result of the operation
    EXPECT_FALSE(consumer.doCriticalWork());
}
