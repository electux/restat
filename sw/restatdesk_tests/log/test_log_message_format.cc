////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_message_format.cc
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
/// @brief Test the content and formatting of log messages.
///
/// Verifies that the Logger produces correctly formatted output strings.
/// Validates the presence of the ISO 8601 timestamp separator, the correct
/// severity tag (e.g., [ERROR]), and the exact message content.
///
/// @param LogTest The test fixture.
/// @param LogMessageFormatTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, LogMessageFormatTest)
{
	m_logger.setLevel(LogLevel::Info);
	m_logger.open();

	const std::string testMsg = "Critical System Failure";
	m_logger.log(testMsg, LogLevel::Error);

	const std::string output = getLastLine();

	// Verify timestamp format (T separator for ISO 8601)
	EXPECT_NE(output.find("T"), std::string::npos);
	// Verify severity tag
	EXPECT_NE(output.find("[ERROR]"), std::string::npos);
	// Verify message payload
	EXPECT_NE(output.find(testMsg), std::string::npos);

	m_logger.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log message filtering based on log levels.
///
/// Verifies that the Logger produces correctly formatted output strings.
///
/// @param LogTest The test fixture.
/// @param AllLevelFilteringTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, AllLevelFilteringTest)
{
    m_logger.open();

    // Set level to Warning (1)
    m_logger.setLevel(LogLevel::Warning);

    // Should Log: Error (0) and Warning (1)
    m_logger.log("Error msg", LogLevel::Error);
    m_logger.log("Warning msg", LogLevel::Warning);
    // Should NOT Log: Info (2)
    m_logger.log("Info msg", LogLevel::Info);

    std::ifstream file(m_testFileName);
    std::string line;
    int count = 0;
    while (std::getline(file, line)) { count++; }
    
    EXPECT_EQ(count, 2); // Only Error and Warning should be present
}
