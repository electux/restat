////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_open.cc
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

#include <sys/stat.h>
#include "test_log.h"

using namespace Electux::App::Logger;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the file opening and basic lifecycle of the Logger.
///
/// Verifies that the logger can successfully create and open the designated
/// log file on the filesystem and properly release the resource upon closing.
///
/// @param LogTest The test fixture.
/// @param FileOpenTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, FileOpenTest)
{
	// Should fail if no output file is set (handled in SetUp, but testing logic)
	EXPECT_TRUE(m_logger.open());
	EXPECT_TRUE(std::filesystem::exists(m_testFileName));
	EXPECT_TRUE(m_logger.close());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test that calling open() multiple times does not cause errors.
///
/// Verifies that calling open() multiple times does not cause errors and that the
/// logger remains in a valid state, allowing for idempotent open operations.
///
/// @param LogTest The test fixture.
/// @param DoubleOpenTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, DoubleOpenTest)
{
    // Test double open
    EXPECT_TRUE(m_logger.open());
    EXPECT_TRUE(m_logger.open()); // Should still be true/ready
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test open functionality when file permissions prevent writing.
///
/// Creates a temporary log file, removes write permissions, and verifies
/// that the open() method fails gracefully. Restores permissions afterward.
///
/// @param LogTest The test fixture.
/// @param OpenFailureTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, OpenFailureTest)
{
	// Create a dummy file
	{
		std::ofstream ofs(m_testFileName);
		ofs << "dummy content";
	}

	// Remove write permissions
	chmod(m_testFileName.c_str(), S_IRUSR); // Read only

	EXPECT_FALSE(m_logger.open());

	chmod(m_testFileName.c_str(), S_IWUSR | S_IRUSR);
}
