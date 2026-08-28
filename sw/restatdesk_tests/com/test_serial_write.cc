////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_write.cc
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
/// @brief Test writing to a closed serial port.
///
/// Verifies that attempting to write to a serial port that has not been
/// opened does not cause a crash.
///
/// @param SerialComTest The test fixture.
/// @param WriteToPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, WriteToPortTest)
{
    const std::vector<uint8_t> data_to_write = {0xDE, 0xAD, 0xBE, 0xEF};

    EXPECT_NO_THROW(m_serial.write(data_to_write));
}
