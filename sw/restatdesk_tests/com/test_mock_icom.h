////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_icom.h
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

#include <com/icom.h>
#include <gmock/gmock.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace com::mock
/// @brief Namespace for application communication mocks
namespace com::mock
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Local Type Aliases
	/// @{
    using ICom = Electux::App::Com::ICom;
    /// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class MockICom
    /// @brief Mock implementation of the ICom interface for testing purposes.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class MockICom : public ICom
    {
    public:
        MOCK_METHOD(bool, open, (), (override));
        MOCK_METHOD(bool, close, (), (override));
        MOCK_METHOD(bool, isOpen, (), (const, override));
        MOCK_METHOD(void, read, (std::vector<uint8_t> &data, size_t len), (override));
        MOCK_METHOD(void, write, (const std::vector<uint8_t> &data), (override));
    };
} // namespace com::mock
