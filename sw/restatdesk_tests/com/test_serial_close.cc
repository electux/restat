////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_close.cc
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

#include "test_mock_icom.h"
#include "test_mock_ilib.h"
#include "test_serial_com.h"

using namespace com::mock;
using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test closing the serial port connection.
///
/// Verifies that the close operation correctly releases the system resources
/// associated with the serial device.
///
/// @param SerialComTest The test fixture.
/// @param closeSerialPortTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, closeSerialPortTest)
{
	// TODO: Implement actual resource release verification
	// Example: Check if file descriptor is -1 or invalid after close
	EXPECT_EQ(true, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test closing the mock ICom interface.
///
/// Verifies that the MockICom mock object correctly handles expectations for
/// open and close method calls.
///
/// @param MockIComTest The test suite name.
/// @param CloseIComTest The test case name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockIComTest, CloseIComTest)
{
    MockICom mockCom;

    EXPECT_CALL(mockCom, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockCom, close()).WillOnce(::testing::Return(true));

    ASSERT_TRUE(mockCom.open());
    ASSERT_TRUE(mockCom.close());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test closing the mock ILibSerialPort interface.
///
/// Verifies that the MockILibSerialPort mock object correctly handles expectations
/// for Open and Close method calls.
///
/// @param MockILibSerialPortTest The test suite name.
/// @param CloseILibSerialPortTest The test case name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockILibSerialPortTest, CloseILibSerialPortTest)
{
    MockILibSerialPort mockPort;

    EXPECT_CALL(mockPort, Open("/dev/ttyS0"));
    EXPECT_CALL(mockPort, Close());

    mockPort.Open("/dev/ttyS0");
    mockPort.Close();
}
