////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_ilib.h
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
#include <com/serial/serialw/ilib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace com::mock
/// @brief Namespace for application communication mocks
namespace com::mock
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @name Local Type Aliases
	/// @{
    using ILibSerialPort = Electux::App::Com::ILibSerialPort;
    using BaudRate = Electux::App::Com::BaudRate;
    using CharacterSize = Electux::App::Com::CharacterSize;
    using Parity = Electux::App::Com::Parity;
    using StopBits = Electux::App::Com::StopBits;
    using FlowControl = Electux::App::Com::FlowControl;
    /// @}
	////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class MockILibSerialPort
    /// @brief Mock implementation of the ILibSerialPort interface for testing purposes.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class MockILibSerialPort : public ILibSerialPort
    {
    public:
        MOCK_METHOD(void, Open, (const std::string &device), (override));
        MOCK_METHOD(void, Close, (), (override));
        MOCK_METHOD(bool, IsOpen, (), (const, override));
        MOCK_METHOD(void, Read, (std::vector<uint8_t> &data, size_t len), (override));
        MOCK_METHOD(void, Write, (const std::vector<uint8_t> &data), (override));
        MOCK_METHOD(void, SetBaudRate, (BaudRate baudRate), (override));
        MOCK_METHOD(void, SetCharacterSize, (CharacterSize characterSize), (override));
        MOCK_METHOD(void, SetParity, (Parity parity), (override));
        MOCK_METHOD(void, SetStopBits, (StopBits stopBits), (override));
        MOCK_METHOD(void, SetFlowControl, (FlowControl flowControl), (override));
    };
} // namespace com::mock
