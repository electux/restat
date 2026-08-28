////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_state.h
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

#include <model/channel_types.h>
#include <string_view>
#include <sys/types.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Model::Channel
/// @brief Namespace for channel-related configuration parameters and state
namespace Electux::App::Model::Channel {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The total number of communication channels supported by the
    /// system
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr const ssize_t cNumOfChannels = 8;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Internal Home Slot Constants
    /// @{
    constexpr std::string_view cEmptyString = "";
    constexpr std::string_view cSpaceString = " ";
    constexpr char cSpaceDelimiter = ' ';
    constexpr std::string_view cTrue = "true";
    constexpr std::string_view cFalse = "false";
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    struct ChannelState {
        bool enabled{false};
        ChannelMode mode{ChannelMode::Unknown};
        bool toggle{false};
        int timer{0};
        bool timerEnabled{false};
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Converts a boolean value to its string representation.
    /// @param value Boolean value to convert.
    /// @return "true" if value is true, "false" otherwise.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    constexpr std::string_view boolToString(bool value) {
        return value ? cTrue : cFalse;
    }
} // namespace Electux::App::Model::Channel
