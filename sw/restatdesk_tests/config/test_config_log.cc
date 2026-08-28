////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_log.cc
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
/// @brief Test the log configuration functionality of ConfigManager.
///
/// Verifies that the configuration manager correctly loads and retrieves
/// logging parameters, ensuring that the log file path is defined and 
/// the default log level is set to 'Info'.
///
/// @param ConfigManagerTest The test fixture.
/// @param LogConfigTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, LogConfigTest)
{
	m_config->init();
	m_config->load();
	const auto& logCfg = m_config->getConfig();

	auto filePathKey = logCfg.toString(ModelLogKey::FilePath);
	auto logLevelKey = logCfg.toString(ModelLogKey::LogLevel);

	EXPECT_FALSE(logCfg.getEntity(filePathKey).empty());
	EXPECT_EQ(logCfg.getEntity(logLevelKey), "2");
}
