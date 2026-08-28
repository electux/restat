////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_close.cc
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
/// @brief Test the file opening and closing operations of the Logger.
///
/// Verifies that the logger can correctly establish a connection to the 
/// output file and subsequently release the file descriptor without errors.
///
/// @param LogTest The test fixture.
/// @param CloseTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, CloseTest)
{
	m_logger.open();

	// Verify that the file was created and is accessible
	EXPECT_TRUE(std::filesystem::exists(m_testFileName));
	// Now test closing the file stream
	EXPECT_TRUE(m_logger.close());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the behavior of the close() method when called multiple times.
///
/// Ensures that the method handles idempotent calls gracefully without
/// throwing exceptions or causing errors.
///
/// @param LogTest The test fixture.
/// @param DoubleCloseIsOkTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, DoubleCloseIsOkTest)
{
    m_logger.open();

    // Test double close
    EXPECT_TRUE(m_logger.close());
	// Second close should return true as stream is already closed
    EXPECT_TRUE(m_logger.close());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test that the destructor properly closes the log file stream.
///
/// Ensures that the method handles idempotent calls gracefully without
/// throwing exceptions or causing errors.
///
/// @param LogTest The test fixture.
/// @param DestructorClosesFileTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, DestructorClosesFileTest)
{
    {
        Log tempLogger;
        tempLogger.setOutputFile("destructor_test.log");
        EXPECT_TRUE(tempLogger.open());
        // tempLogger goes out of scope here, calling ~Log() -> close()
    }

    // If closed properly, we should be able to remove the file immediately
    EXPECT_TRUE(std::filesystem::remove("destructor_test.log"));
}
