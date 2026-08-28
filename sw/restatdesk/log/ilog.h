////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ilog.h
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

#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Logger
/// @brief Namespace for application logging components
namespace Electux::App::Logger {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum LogLevel
    /// @brief Defines the severity levels for log messages.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class LogLevel : uint8_t {
        Error = 0, ///< Critical errors or failures
        Warning,   ///< Non-critical issues or warnings
        Info       ///< General informational messages
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ILog
    /// @brief Interface for logging implementations.
    ///
    /// This interface defines the standard operations for a logger, including
    /// level filtering, managing the logging sink connection, and writing logs.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ILog {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor for the ILog interface.
        /// Ensures proper cleanup of derived logger implementations.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ILog() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Specific to File Logger: Sets the destination file path.
        /// @param output The absolute or relative path to the log file.
        /// Implementation should handle the specifics of output such as file
        /// path.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setOutputFile(const std::string &output) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the filtering log level.
        /// @param level The log level to set for filtering messages.
        /// Implementation should handle the specifics of setting filtering
        /// messages.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setLevel(LogLevel level) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the current filtering log level.
        /// @return The current log level used for filtering messages.
        /// Implementation should handle the specifics of getting filtering
        /// messages.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual LogLevel getLevel() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the logging sink (e.g., file, socket, console).
        /// @return true if the sink was successfully opened, otherwise false.
        /// Implementation should handle the specifics of opening log file.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool open() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the logging sink.
        /// @return true if the sink was successfully closed, otherwise false.
        /// Implementation should handle the specifics of closing log file.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool close() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Logs a message to the active sink.
        /// @param message The string content to be logged.
        /// @param level The severity level of the log message.
        /// Implementation should handle the specifics of logging messages.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void log(const std::string &message, LogLevel level) = 0;
    };
} // namespace Electux::App::Logger
