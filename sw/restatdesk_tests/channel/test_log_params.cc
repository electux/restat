////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_params.cc
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
#include <log/log_level_params.h>

using namespace Electux::App::Logger::LogLevels;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log levels array.
///
/// @param ParamsLogLevelsTest The name of the test case.
/// @param LogLevelsArrayTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsLogLevelsTest, LogLevelsArrayTest)
{
    EXPECT_EQ(cLogLevels[0], "Error");
    EXPECT_EQ(cLogLevels[1], "Warning");
    EXPECT_EQ(cLogLevels[2], "Info");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log level error constant.
///
/// @param ParamsLogLevelsTest The name of the test case.
/// @param LogLevelErrorTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsLogLevelsTest, LogLevelErrorTest)
{
    EXPECT_EQ(clogLevelError, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log level warning constant.
///
/// @param ParamsLogLevelsTest The name of the test case.
/// @param LogLevelWarningTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsLogLevelsTest, LogLevelWarningTest)
{
    EXPECT_EQ(clogLevelWarning, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test log level info constant.
///
/// @param ParamsLogLevelsTest The name of the test case.
/// @param LogLevelInfoTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParamsLogLevelsTest, LogLevelInfoTest)
{
    EXPECT_EQ(clogLevelInfo, 2);
}
