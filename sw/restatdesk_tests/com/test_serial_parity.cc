////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_parity.cc
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

#include "test_serial_com.h"
#include <com/serial/serial_com_params.h>
#include <com/serial/serial_utils.h>

using namespace Electux::App::Com;
using namespace Electux::App::Com::SerialComConstants;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test bidirectional conversion of all supported Parity modes.
///
/// This parameterized test iterates through all valid Parity mappings to 
/// ensure that the internal conversion logic (enum to uint and vice versa) 
/// is consistent and matches the expected system constants.
///
/// @param ParityTest The name of the test case.
/// @param ParityConversionTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_P(ParityTest, ParityConversionTest)
{
	const ParameterMapping<Parity> params = this->GetParam();

	EXPECT_EQ(SerialUtils::parityToUint(params.enum_val), params.uint_val);
	EXPECT_EQ(SerialUtils::uintToParity(params.uint_val), params.enum_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Define the test suite instance with all supported parity values.
///
/// These values correspond to the switch-case logic found in serial_com_utils.cc.
///
/// @param SerialComTest The name of the test suite.
/// @param ParityTest The name of the parameterized test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P
(
	SerialComTest,
	ParityTest,
	::testing::Values
	(
		ParameterMapping<Parity>{Parity::PARITY_NONE, 2},
		ParameterMapping<Parity>{Parity::PARITY_ODD,  1},
		ParameterMapping<Parity>{Parity::PARITY_EVEN, 0}
	)
);

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test detection of invalid parity parameters.
///
/// Verifies that the conversion logic correctly identifies unsupported 
/// parity modes and returns the predefined invalid parameter 
/// constant or enum.
///
/// @param SerialComTest The name of the test suite.
/// @param InvalidParityDetectionTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, InvalidParityDetectionTest)
{
	uint32_t invalid_uint = SerialUtils::parityToUint(Parity::PARITY_INVALID);
	EXPECT_EQ(invalid_uint, cComInvalidParameter);

	Parity invalid_enum = SerialUtils::uintToParity(9);
	EXPECT_EQ(invalid_enum, Parity::PARITY_INVALID);
}
