////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mock_config.h
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

#include <gmock/gmock.h>
#include <config/iconfig.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Config
/// @brief Namespace for application configuration management
namespace Electux::App::Config
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Local Type Aliases
	/// @{
	using Model = Electux::App::Model::Model;
	/// @}
	////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class MockConfig
	/// @brief Mock implementation of the IConfig interface.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class MockConfig : public IConfig
	{
	public:
		MOCK_METHOD(void, init, (), (override));
		MOCK_METHOD(bool, load, (), (override));
		MOCK_METHOD(bool, store, (), (override));
		MOCK_METHOD(void, setConfig, (const Model& config), (override));
		MOCK_METHOD(const Model&, getConfig, (), (const, override));
	};
} // namespace Electux::App::Config
