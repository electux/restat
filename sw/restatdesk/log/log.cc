////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// log.cc
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

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <log/log.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Logger
/// @brief Namespace for application logging components
namespace Electux::App::Logger {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Internal Formatting Constants
    /// @{
    static constexpr std::string_view TAG_ERROR =
        "[ERROR] "; ///< Tag for error messages
    static constexpr std::string_view TAG_WARN =
        "[WARN]  "; ///< Tag for warning messages
    static constexpr std::string_view TAG_INFO =
        "[INFO]  "; ///< Tag for info messages
    static constexpr const char *cTimestampFormat = "%Y-%m-%dT%H:%M:%S";
    static constexpr const char *cOutputNotSetError =
        "Output file path is not set. Cannot open log stream.";
    static constexpr const char *cCloseStreamError =
        "Failed to close log stream for file: ";
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Electux::App::Logger

using namespace Electux::App::Logger;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destructor for the Log class.
/// Calls close() to ensure the file stream is flushed and closed safely.
////////////////////////////////////////////////////////////////////////////////////////////////////////
Log::~Log() { close(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the destination file path for the logger.
/// @param output The path to the log file.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Log::setOutputFile(const std::string &output) { m_outputFile = output; }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the filtering log level.
/// @param level The log level to set (Error, Warning, or Info).
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Log::setLevel(LogLevel level) { m_level = level; }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets the current filtering log level.
/// @return The current LogLevel enum value.
////////////////////////////////////////////////////////////////////////////////////////////////////////
LogLevel Log::getLevel() const { return m_level; }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the log file stream.
/// Uses std::ios::app to append to existing file content.
/// @return true if the stream is ready for writing, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Log::open() {
    std::lock_guard<std::mutex> lk(m_mutex);

    // If already open, return true
    if (m_stream.is_open()) {
        return true;
    }

    // Validate that an output file path has been set
    if (m_outputFile.empty()) {
        std::cerr << cOutputNotSetError << std::endl;
        return false;
    }

    m_stream.open(m_outputFile, std::ios::out | std::ios::app);
    return m_stream.is_open();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Closes the log file stream.
/// @return true if the stream was open or closed and is now closed, false
/// otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Log::close() {
    std::lock_guard<std::mutex> lk(m_mutex);

    if (!m_stream.is_open()) {
        // Stream is already closed, consider this a successful close operation
        return true;
    }

    // Attempt to close the stream
    m_stream.close();

    if (m_stream.fail()) {
        // If closing failed, clear the error state to allow future operations
        m_stream.clear();
        // Log the error to stderr for debugging purposes
        std::cerr << cCloseStreamError << m_outputFile << std::endl;
        return false;
    }

    // Successfully closed the stream
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Formats and writes a log entry.
///
/// Processes the message by:
/// 1. Checking if the stream is open.
/// 2. Filtering based on the current log level.
/// 3. Generating a ISO 8601 timestamp (YYYY-MM-DDTHH:MM:SS).
/// 4. Appending the appropriate severity tag.
/// 5. Flushing the stream to ensure data is written to disk immediately.
///
/// @param message The text content to log.
/// @param level The severity of the entry.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Log::log(const std::string &message, LogLevel level) {
    std::lock_guard<std::mutex> lk(m_mutex);

    if (!m_stream.is_open()) {
        return;
    }

    if (static_cast<int>(level) > static_cast<int>(m_level)) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm);

    m_stream << std::put_time(&tm, cTimestampFormat) << " ";

    switch (level) {
    case LogLevel::Error:
        m_stream << TAG_ERROR;
        break;
    case LogLevel::Warning:
        m_stream << TAG_WARN;
        break;
    case LogLevel::Info:
        m_stream << TAG_INFO;
        break;
    }

    m_stream << message << std::endl;
    m_stream.flush();
}
