////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_read.cc
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

#include "test_serial_com.h"

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test reading from a closed serial port.
///
/// Verifies that attempting to read from a serial port that has not been
/// opened does not cause a crash and leaves the data buffer unchanged.
///
/// @param SerialComTest The test fixture.
/// @param ReadFromPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, ReadFromPortTest)
{
    std::vector<uint8_t> buffer;

    EXPECT_NO_THROW(m_serial.read(buffer, 10));
    EXPECT_TRUE(buffer.empty());
}
