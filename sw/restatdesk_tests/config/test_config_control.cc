////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config_control.cc
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
/// @brief Test the control configuration functionality of ConfigManager.
///
/// Verifies that the configuration manager correctly loads and retrieves
/// control-related parameters, ensuring that keys like 'Enable' and 'Timer'
/// match the expected default values.
///
/// @param ConfigManagerTest The test fixture.
/// @param ControlConfigTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(ConfigManagerTest, ControlConfigTest)
{
	m_config->init();
	m_config->load();
	const auto& control = m_config->getConfig();

	auto enableKey = control.toString(ModelControlKey::Enable);
	auto timerKey = control.toString(ModelControlKey::Timer);

	EXPECT_EQ(control.getEntity(enableKey), "false false false false false false false false");
	EXPECT_EQ(control.getEntity(timerKey), "0 0 0 0 0 0 0 0");
}
