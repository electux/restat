////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// log_level_params.h
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
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdint>
#include <string_view>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Logger::LogLevels
/// @brief Namespace for log level configuration parameters
namespace Electux::App::Logger::LogLevels {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Log Levels Definitions
    /// @{
    /// @brief Array of string representations for log levels
    constexpr std::string_view cLogLevels[]{"Error", "Warning", "Info"};
    /// @brief Constant index for the Error log level
    constexpr const uint32_t clogLevelError = 0;
    /// @brief Constant index for the Warning log level
    constexpr const uint32_t clogLevelWarning = 1;
    /// @brief Constant index for the Info log level
    constexpr const uint32_t clogLevelInfo = 2;
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Electux::App::Logger::LogLevels
