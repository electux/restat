////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_serial_data_bits.cc
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
/// @brief Test bidirectional conversion of all supported Character sizes.
///
/// This parameterized test iterates through all valid Data Bits mappings to 
/// ensure that the internal conversion logic (enum to uint and vice versa) 
/// is consistent and matches the expected system constants.
///
/// @param DataBitsTest The name of the test case.
/// @param DataBitsConversionTest The name of the test.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_P(DataBitsTest, DataBitsConversionTest)
{
	const ParameterMapping<CharacterSize> params = this->GetParam();

	EXPECT_EQ(SerialUtils::dataBitsToUint(params.enum_val), params.uint_val);
	EXPECT_EQ(SerialUtils::uintToDataBits(params.uint_val), params.enum_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Define the test suite instance with all supported data bits values.
///
/// These values correspond to the switch-case logic found in serial_com_utils.cc.
///
/// @param SerialComTest The name of the test suite.
/// @param DataBitsTest The name of the parameterized test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
INSTANTIATE_TEST_SUITE_P
(
	SerialComTest,
	DataBitsTest,
	::testing::Values
	(
		ParameterMapping<CharacterSize>{CharacterSize::CHAR_SIZE_5, 0},
		ParameterMapping<CharacterSize>{CharacterSize::CHAR_SIZE_6, 1},
		ParameterMapping<CharacterSize>{CharacterSize::CHAR_SIZE_7, 2},
		ParameterMapping<CharacterSize>{CharacterSize::CHAR_SIZE_8, 3}
	)
);

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test detection of invalid data bits parameters.
///
/// Verifies that the conversion logic correctly identifies unsupported 
/// character sizes (outside the 5-8 range) and returns the predefined 
/// invalid parameter constant or enum.
///
/// @param SerialComTest The name of the test suite.
/// @param InvalidDataBitsDetectionTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(SerialComTest, InvalidDataBitsDetectionTest)
{
	uint32_t invalid_uint = SerialUtils::dataBitsToUint(CharacterSize::CHAR_SIZE_INVALID);
	EXPECT_EQ(invalid_uint, cComInvalidParameter);

	CharacterSize invalid_enum = SerialUtils::uintToDataBits(9);
	EXPECT_EQ(invalid_enum, CharacterSize::CHAR_SIZE_INVALID);
}
