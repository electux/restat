////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_serial.cc
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

#include "test_config.h"

using namespace Electux::App::Model;
using namespace Electux::App::Config;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the serial configuration functionality of ConfigManager.
///
/// Verifies that the configuration manager correctly loads and retrieves
/// serial communication parameters, ensuring that device path, baud rate,
/// and data bits match the expected system defaults.
///
/// @param ConfigManagerTest The test fixture.
/// @param SerialConfigTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, SerialConfigTest)
{
	m_config->init();
	m_config->load();
	const auto& serial = m_config->getConfig();

	auto deviceKey = serial.toString(ModelSerialKey::Device);
	auto baudKey = serial.toString(ModelSerialKey::Baud);
	auto dataKey = serial.toString(ModelSerialKey::Data);

	EXPECT_EQ(serial.getEntity(deviceKey), "/dev/ttyUSB0");
	EXPECT_EQ(serial.getEntity(baudKey), "10");
	EXPECT_EQ(serial.getEntity(dataKey), "3");
}
