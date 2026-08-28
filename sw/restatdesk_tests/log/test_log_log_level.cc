////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_log_level.cc
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
/// @brief Test the management of logging levels.
///
/// Verifies that the Logger correctly updates and maintains its internal 
/// log level state. Ensures that the setLevel and getLevel methods are 
/// consistent across different LogLevel values.
///
/// @param LogTest The test fixture.
/// @param LevelManagementTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, LevelManagementTest)
{
	m_logger.setLevel(LogLevel::Error);
	EXPECT_EQ(m_logger.getLevel(), LogLevel::Error);

	m_logger.setLevel(LogLevel::Info);
	EXPECT_EQ(m_logger.getLevel(), LogLevel::Info);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the default log level.
///
/// Verifies that the Logger is initialized with the expected default log level (Info).
///
/// @param LogTest The test fixture.
/// @param DefaultLevelTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, DefaultLevelTest)
{
	EXPECT_EQ(m_logger.getLevel(), LogLevel::Info);
}
