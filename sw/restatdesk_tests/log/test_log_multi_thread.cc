////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log_multi_thread.cc
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

#include <thread>
#include <vector>
#include <algorithm>
#include "test_log.h"

using namespace Electux::App::Logger;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Test thread safety by logging from multiple threads simultaneously.
///
/// Verifies that the Logger class can handle concurrent log requests from 
/// multiple execution threads without race conditions, ensuring that every 
/// message is correctly serialized and written to the output file.
///
/// @param LogTest The test fixture.
/// @param MultiThreadedLoggingTest The name of the test case.
////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(LogTest, MultiThreadedLoggingTest)
{
	m_logger.open();
	const int threadCount = 10;
	std::vector<std::thread> threads;

	for (int i = 0; i < threadCount; ++i)
	{
		threads.emplace_back([this, i]() {
			m_logger.log("Thread message " + std::to_string(i), LogLevel::Info);
		});
	}

	for (auto &t : threads)
	{
		t.join();
	}

	// Verify that all lines were written correctly
	std::ifstream file(m_testFileName);
	int lineCount = std::count(std::istreambuf_iterator<char>(file),
	                           std::istreambuf_iterator<char>(), '\n');

	EXPECT_EQ(lineCount, threadCount);
	m_logger.close();
}
