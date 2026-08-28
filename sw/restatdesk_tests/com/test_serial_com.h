////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_com.h
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

#include <gtest/gtest.h>
#include <iostream>
#include <com/serial/serial_com.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Com
/// @brief Namespace for serial communication and related unit tests
namespace Electux::App::Com
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class SerialComProxy
	/// @brief Proxy class to expose protected SerialCom methods for testing.
	///
	/// This class uses inheritance to promote internal conversion methods
	/// to public visibility, allowing GoogleTest to verify the accuracy
	/// of parameter mappings (baud, parity, etc.).
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SerialComProxy : public SerialCom
	{
	public:
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class SerialComTest
	/// @brief Test fixture for SerialCom class.
	///
	/// Provides a controlled environment and instance of SerialComProxy
	/// to perform unit testing on serial communication logic.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class SerialComTest : public ::testing::Test
	{
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Local Type Aliases
		/// @{
		using SerialCom = Electux::App::Com::SerialComProxy;
		using BaudRate = Electux::App::Com::BaudRate;
		using CharacterSize = Electux::App::Com::CharacterSize;
		using Parity = Electux::App::Com::Parity;
		using StopBits = Electux::App::Com::StopBits;
		using FlowControl = Electux::App::Com::FlowControl;
		using SerialParams = Electux::App::Com::SerialParams;
		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief The instance being tested (SerialComProxy).
		////////////////////////////////////////////////////////////////////////////////////////////////
		SerialCom m_serial{};

		void SetUp() override
		{

		}

		void TearDown() override
		{

		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @struct ParameterMapping
	/// @brief Structure to hold enum and corresponding uint32_t values for testing.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct ParameterMapping
	{
		T enum_val;
		uint32_t uint_val;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class SerialParamTest
	/// @brief Base parameterized test class for all serial parameters.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class SerialParamTest : public SerialComTest,
	                        public ::testing::WithParamInterface<ParameterMapping<T>>
	{
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Type aliases for specific parameter tests to improve readability in test cases.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	using BaudRateTest = SerialParamTest<BaudRate>;
	using DataBitsTest = SerialParamTest<CharacterSize>;
	using ParityTest = SerialParamTest<Parity>;
	using StopBitsTest = SerialParamTest<StopBits>;
	using FlowControlTest = SerialParamTest<FlowControl>;
} // namespace Electux::App::Com
