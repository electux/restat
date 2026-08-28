////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_params.cc
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

#include <gtest/gtest.h>
#include <com/serial/serial_com_params.h>

using namespace Electux::App::Com::SerialComConstants;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test baud rates array.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComBaudRatesArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComBaudRatesArrayTest)
{
    EXPECT_EQ(cComBaudRates[cComBaud110], "110");
    EXPECT_EQ(cComBaudRates[cComBaud300], "300");
    EXPECT_EQ(cComBaudRates[cComBaud600], "600");
    EXPECT_EQ(cComBaudRates[cComBaud1200], "1200");
    EXPECT_EQ(cComBaudRates[cComBaud2400], "2400");
    EXPECT_EQ(cComBaudRates[cComBaud4800], "4800");
    EXPECT_EQ(cComBaudRates[cComBaud9600], "9600");
    EXPECT_EQ(cComBaudRates[cComBaud19200], "19200");
    EXPECT_EQ(cComBaudRates[cComBaud38400], "38400");
    EXPECT_EQ(cComBaudRates[cComBaud57600], "57600");
    EXPECT_EQ(cComBaudRates[cComBaud115200], "115200");
    EXPECT_EQ(cComBaudRates[cComBaud230400], "230400");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test baud rate constants.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComBaudRatesConstantsTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComBaudRatesConstantsTest)
{
    EXPECT_EQ(cComBaud110, 0);
    EXPECT_EQ(cComBaud300, 1);
    EXPECT_EQ(cComBaud600, 2);
    EXPECT_EQ(cComBaud1200, 3);
    EXPECT_EQ(cComBaud2400, 4);
    EXPECT_EQ(cComBaud4800, 5);
    EXPECT_EQ(cComBaud9600, 6);
    EXPECT_EQ(cComBaud19200, 7);
    EXPECT_EQ(cComBaud38400, 8);
    EXPECT_EQ(cComBaud57600, 9);
    EXPECT_EQ(cComBaud115200, 10);
    EXPECT_EQ(cComBaud230400, 11);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test data bits array.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComDataBitsArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComDataBitsArrayTest)
{
    EXPECT_EQ(cComDataBits[cComDataBits5], "5");
    EXPECT_EQ(cComDataBits[cComDataBits6], "6");
    EXPECT_EQ(cComDataBits[cComDataBits7], "7");
    EXPECT_EQ(cComDataBits[cComDataBits8], "8");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test data bits constants.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComDataBitsConstantsTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComDataBitsConstantsTest)
{
    EXPECT_EQ(cComDataBits5, 0);
    EXPECT_EQ(cComDataBits6, 1);
    EXPECT_EQ(cComDataBits7, 2);
    EXPECT_EQ(cComDataBits8, 3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test parities array.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComParitiesArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComParitiesArrayTest)
{
    EXPECT_EQ(cComParities[cComParityEven], "Even");
    EXPECT_EQ(cComParities[cComParityOdd], "Odd");
    EXPECT_EQ(cComParities[cComParityNone], "None");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test parity constants.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComParityConstantsTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComParityConstantsTest)
{
    EXPECT_EQ(cComParityEven, 0);
    EXPECT_EQ(cComParityOdd, 1);
    EXPECT_EQ(cComParityNone, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test stop bits array.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComStopBitsArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComStopBitsArrayTest)
{
    EXPECT_EQ(cComStopBits[cComStopBits1], "1");
    EXPECT_EQ(cComStopBits[cComStopBits2], "2");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test stop bits constants.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComStopBitsConstantsTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComStopBitsConstantsTest)
{
    EXPECT_EQ(cComStopBits1, 0);
    EXPECT_EQ(cComStopBits2, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test flow controls array.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComFlowControlsArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComFlowControlsArrayTest)
{
    EXPECT_EQ(cComFlowControls[cComFlowControlNone], "None");
    EXPECT_EQ(cComFlowControls[cComFlowControlHw], "Hardware");
    EXPECT_EQ(cComFlowControls[cComFlowControlSw], "Software");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test flow control constants.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComFlowControlConstantsTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComFlowControlConstantsTest)
{
    EXPECT_EQ(cComFlowControlNone, 0);
    EXPECT_EQ(cComFlowControlHw, 1);
    EXPECT_EQ(cComFlowControlSw, 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test invalid parameter constant.
///
/// @param ParamsSerialComTest The name of the test case.
/// @param ComInvalidParameterTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsSerialComTest, ComInvalidParameterTest)
{
    EXPECT_EQ(cComInvalidParameter, 127);
}
