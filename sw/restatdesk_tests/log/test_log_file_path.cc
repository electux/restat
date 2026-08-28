////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_file_path.cc
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
/// @brief Test setting and verifying the output file path.
///
/// Verifies that the logger correctly accepts a new file path and that it
/// can successfully open a file stream at that location on the filesystem.
///
/// @param LogTest The test fixture.
/// @param SetOutputFileTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, SetOutputFileTest)
{
	std::string path = "subdir_test.log";
	m_logger.setOutputFile(path);

	// Attempt to open the log file stream and verify it was created
	EXPECT_TRUE(m_logger.open());
	// Check that the file now exists on the filesystem
	EXPECT_TRUE(std::filesystem::exists(path));
	m_logger.close();
	std::filesystem::remove(path);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test logger behavior when no file path is configured.
///
/// Ensures that the logger's protection logic prevents opening a file stream
/// when the target output path is empty or not set.
///
/// @param LogTest The test fixture.
/// @param EmptyFilePathIsWithoutEffectTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, EmptyFilePathIsWithoutEffectTest)
{
	// Ensure path is empty (default state)
	// Clear the test file name to simulate empty path
	m_logger.setOutputFile("");

	// Attempt to open the log file stream and expect failure
	EXPECT_FALSE(m_logger.open());
}
