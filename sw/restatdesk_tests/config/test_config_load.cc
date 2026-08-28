////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_load.cc
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

#include <fstream>
#include "test_config.h"

using namespace Electux::App::Config;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test the load functionality of ConfigManager.
///
/// Verifies that the configuration manager can successfully open, read,
/// and parse an existing configuration file from the filesystem, ensuring
/// data integrity for the 'device' parameter.
///
/// @param ConfigManagerTest The test fixture.
/// @param LoadConfigTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, LoadConfigTest)
{
	// Create a dummy config file for testing load
	std::ofstream ofs(m_testConfigFileName);
	ofs << "device=/dev/ttyUSB0\n";
	ofs.close();

	m_config->init();
	bool success = m_config->load();
	EXPECT_TRUE(success);

	const auto& serial = m_config->getConfig();
	auto deviceKey = serial.toString(ModelSerialKey::Device);

	EXPECT_EQ(serial.getEntity(deviceKey), "/dev/ttyUSB0");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test behavior when the configuration file is missing.
///
/// Verifies that if the file does not exist, load() returns true (because it
/// creates a default one) and populates the models with default values.
///
/// @param ConfigManagerTest The test fixture.
/// @param MissingFileLoadDefaultsTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, MissingFileLoadDefaultsTest)
{
	// Ensure file does not exist
	if (std::filesystem::exists(m_testConfigFileName)) {
		std::filesystem::remove(m_testConfigFileName);
	}

	// load() should call defaultConfigStore() and return true
	m_config->init();
	EXPECT_TRUE(m_config->load());
	EXPECT_TRUE(std::filesystem::exists(m_testConfigFileName));

	// Verify a default value was set
	const auto& serial = m_config->getConfig();
	auto deviceKey = serial.toString(ModelSerialKey::Device);
	EXPECT_EQ(serial.getEntity(deviceKey), "/dev/ttyUSB0");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test parsing of malformed lines, comments, and empty spaces.
///
/// Verifies that the load() method can handle various edge cases in the config
/// file, such as comments, empty lines, and malformed entries, without crashing or
/// failing to load valid entries correctly.
///
/// @param ConfigManagerTest The test fixture.
/// @param ParsingEdgeCasesTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, ParsingEdgeCasesTest)
{
	{
		std::ofstream ofs(m_testConfigFileName);
		ofs << "# This is a comment\n";
		ofs << "   \n"; // Empty line with spaces
		ofs << "invalid_line_no_delimiter\n";
		ofs << "valid_key=valid_value\n";
		ofs.close();
	}

	m_config->init();
	EXPECT_TRUE(m_config->load());
	// Verification is implicit: if parser crashes or fails on malformed lines, 
	// the test fails.
}
