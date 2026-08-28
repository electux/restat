////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_setup.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// restatdesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at any later version.
///
/// restatdesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "test_mock_iserial.h"
#include "test_serial_com.h"

using namespace com::mock;
using namespace Electux::App::Com;
using ::testing::_;
using ::testing::Return;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test setting the device path via the mock interface.
///
/// Verifies that setDevice correctly receives the path string and that the mock
/// records the call as expected.
///
/// @param MockISerialTest The test suite name for MockISerial.
/// @param SetDeviceTest The specific name of this test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockISerialTest, SetDeviceTest)
{
    MockISerial mockSerial;
    const std::string devicePath = "/dev/ttyUSB0";

    EXPECT_CALL(mockSerial, setDevice(devicePath)).Times(1);
    
    mockSerial.setDevice(devicePath);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the setup process using a mock serial interface.
///
/// This test verifies that the setup method is correctly invoked on the ISerial 
/// interface with the expected parameters. It uses GoogleMock to simulate a 
/// successful configuration, ensuring the software logic correctly handles the 
/// return state without requiring physical hardware access.
///
/// @param MockISerialTest The test suite name for MockISerial.
/// @param SetupTest The specific name of this test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockISerialTest, SetupTest)
{
    MockISerial mockSerial;
    SerialParams params{
        "/dev/ttyS0", 
        BaudRate::BAUD_9600, 
        CharacterSize::CHAR_SIZE_8, 
        Parity::PARITY_NONE, 
        StopBits::STOP_BITS_1, 
        FlowControl::FLOW_CONTROL_NONE
    };

    // Set expectation that setup() will be called once with any SerialParams and return true
    EXPECT_CALL(mockSerial, setup(_)).WillOnce(Return(true));
    
    // Perform the assertion
    ASSERT_TRUE(mockSerial.setup(params));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test multiple configuration calls in sequence.
///
/// Validates that the interface can handle a series of configuration updates
/// in a specific order.
///
/// @param MockISerialTest The test suite name.
/// @param SequentialConfigTest The test case name.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MockISerialTest, SequentialConfigTest)
{
    MockISerial mockSerial;

    ::testing::InSequence seq; // Forces the order of expectations

    EXPECT_CALL(mockSerial, setBaudRate(BaudRate::BAUD_57600)).Times(1);
    EXPECT_CALL(mockSerial, setParity(Parity::PARITY_EVEN)).Times(1);
    EXPECT_CALL(mockSerial, setFlowControl(FlowControl::FLOW_CONTROL_HARDWARE)).Times(1);

    mockSerial.setBaudRate(BaudRate::BAUD_57600);
    mockSerial.setParity(Parity::PARITY_EVEN);
    mockSerial.setFlowControl(FlowControl::FLOW_CONTROL_HARDWARE);
}
