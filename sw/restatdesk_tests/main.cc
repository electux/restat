////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// main.cc
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

#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Entry point for the unit test suite.
///
/// This function initializes the GoogleTest framework with command-line
/// arguments and executes all test cases registered across the project.
///
/// @param argc The number of command-line arguments.
/// @param argv The array of command-line arguments.
/// @return 0 on success (all tests passed), non-zero otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
