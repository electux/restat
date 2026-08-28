////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_closed_stream.cc
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
/// @brief Test logging behavior when the stream is closed.
///
/// Verifies that the Logger does not write to a closed stream.
///
/// @param LogTest The test fixture.
/// @param LogToClosedStreamIsWithoutEffectTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, LogToClosedStreamIsWithoutEffectTest)
{
    m_logger.setOutputFile(m_testFileName);
    m_logger.close(); // Ensure it's closed

    // Attempting to log should return immediately without writing
    m_logger.log("This should not be written", LogLevel::Error);

    std::ifstream file(m_testFileName);
    EXPECT_EQ(file.peek(), std::ifstream::traits_type::eof());
}
