////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_config.h
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
#pragma once

#include <filesystem>
#include <gtest/gtest.h>
#include <config/config_manager.h>
#include <model/imodel.h>
#include <model/model_factory.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Config
/// @brief Namespace for application configuration management and unit tests
namespace Electux::App::Config
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class ConfigManagerProxy
	/// @brief Proxy class to expose protected ConfigManager methods for testing.
	///
	/// Uses inheritance to promote internal configuration storage and default
	/// setup methods to public visibility, enabling GoogleTest to verify 
	/// internal state and data integrity.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ConfigManagerProxy : public ConfigManager
	{
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Constructor that initializes ConfigManager with a file name.
		/// @param fileName The name of the configuration file.
		////////////////////////////////////////////////////////////////////////////////////////////////
		explicit ConfigManagerProxy(const std::string &fileName) 
			: ConfigManager(Electux::App::Model::createDefault(), fileName) {}

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Promoting protected methods to public for unit testing.
		////////////////////////////////////////////////////////////////////////////////////////////////
		using ConfigManager::defaultConfigStore;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class ConfigManagerTest
	/// @brief Fixture for ConfigManager unit tests.
	///
	/// Provides a controlled environment for testing configuration management,
	/// including automated setup and cleanup of temporary test files.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ConfigManagerTest : public ::testing::Test
	{
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Local Type Aliases
		/// @{
		using ConfigManager = Electux::App::Config::ConfigManagerProxy;
		using ModelControlKey = Electux::App::Model::ModelControlKey;
		using ModelLogKey = Electux::App::Model::ModelLogKey;
		using ModelSerialKey = Electux::App::Model::ModelSerialKey;
		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Test Environment Members
		/// @{
		std::unique_ptr<ConfigManager> m_config; ///< ConfigManagerProxy instance
		const std::string m_testConfigFileName = "test_config"; ///< Test file name
		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////

		void SetUp() override
		{
			m_config = std::make_unique<ConfigManager>(m_testConfigFileName);
		}

		void TearDown() override
		{
			if (std::filesystem::exists(m_testConfigFileName))
			{
				std::filesystem::remove(m_testConfigFileName);
			}
		}
	};
} // namespace Electux::App::Config
