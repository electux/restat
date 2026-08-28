////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_open.cc
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
/// @brief Test opening the serial port connection.
///
/// Ensure that the class handles missing device path gracefully by returning false.
///
/// @param SerialComTest The test fixture.
/// @param OpenSerialPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, OpenSerialPortTest)
{
    EXPECT_FALSE(m_serial.open());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test opening a non-existent serial port.
///
/// Ensures that the class handles invalid device paths gracefully by returning false.
///
/// @param SerialComTest The test fixture.
/// @param OpenInvalidPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, OpenInvalidPortTest)
{
    SerialParams bad_params =
    {
        .device = "/dev/non_existent_device_999",
        .baud = BaudRate::BAUD_9600
    };

    m_serial.setup(bad_params);

    EXPECT_FALSE(m_serial.open());
}

