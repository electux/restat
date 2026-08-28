////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_log.h
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
#include <fstream>
#include <string>
#include <gtest/gtest.h>
#include <log/log.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Logger
/// @brief Namespace for application logging system and its unit tests
namespace Electux::App::Logger
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class LogProxy
	/// @brief Proxy class to inspect internal Log state during unit testing.
	///
	/// This class inherits from Log to provide a way to verify internal
	/// behaviors that are otherwise hidden from the public API.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class LogProxy : public Log
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Helper to check the internal file path.
		/// @return The path to the current output file.
		/// @note Requires m_outputFile to be protected in the base Log class.
		///////////////////////////////////////////////////////////////////////
		std::string getFilePath() const
		{
			return ""; 
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class LogTest
	/// @brief Test fixture for verifying the Logger functionality.
	///
	/// Handles automated setup and teardown of log files to ensure tests
	/// are isolated and clean.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class LogTest : public ::testing::Test
	{
	protected:
		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Local Type Aliases
		/// @{
		using Log = Electux::App::Logger::Log;
		using LogLevel = Electux::App::Logger::LogLevel;
		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @name Test Members
		/// @{
		Log m_logger{};                             ///< Logger instance under test
		const std::string m_testFileName = "test_output.log"; ///< Temporary log file
		/// @}
		////////////////////////////////////////////////////////////////////////////////////////////////

		void SetUp() override
		{
			if (std::filesystem::exists(m_testFileName))
			{
				std::filesystem::remove(m_testFileName);
			}

			m_logger.setOutputFile(m_testFileName);
		}

		void TearDown() override
		{
			m_logger.close();
			if (std::filesystem::exists(m_testFileName))
			{
				std::filesystem::remove(m_testFileName);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Helper to read the last line of the log file.
		/// @return A string containing the last recorded log entry.
		////////////////////////////////////////////////////////////////////////////////////////////////
		std::string getLastLine()
		{
			std::ifstream file(m_testFileName);
			std::string line, lastLine;

			while (std::getline(file, line))
			{
				if (!line.empty())
				{
					lastLine = line;
				}
			}

			return lastLine;
		}
	};
} // namespace Electux::App::Logger
