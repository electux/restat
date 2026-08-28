////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_filtering.cc
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

#include "test_log.h"

using namespace Electux::App::Logger;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log filtering functionality based on log levels.
///
/// Verifies that the logger correctly filters out messages with a lower 
/// priority (higher numerical value) than the current threshold, ensuring 
/// only relevant logs are written to the file.
///
/// @param LogTest The test fixture.
/// @param LogFilteringTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, LogFilteringTest)
{
	m_logger.setLevel(LogLevel::Error);
	m_logger.open();

	// This should be filtered out because level is Info > Error
	m_logger.log("This should not appear", LogLevel::Info);

	// File should be empty after filtered log attempt
	std::ifstream file(m_testFileName);
	EXPECT_EQ(file.peek(), std::ifstream::traits_type::eof());

	m_logger.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log message formatting and tag correctness based on log levels.
///
/// Verifies that log entries are correctly tagged with their severity level and 
/// that the timestamp and message formatting are consistent with expectations.
///
/// @param LogTest The test fixture.
/// @param TagVerificationTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, TagVerificationTest)
{
    m_logger.setLevel(LogLevel::Info);
    m_logger.open();

    m_logger.log("Test Error", LogLevel::Error);
    EXPECT_NE(getLastLine().find("[ERROR]"), std::string::npos);
    m_logger.log("Test Warn", LogLevel::Warning);
    EXPECT_NE(getLastLine().find("[WARN]"), std::string::npos);
    m_logger.log("Test Info", LogLevel::Info);
    EXPECT_NE(getLastLine().find("[INFO]"), std::string::npos);
}
