////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_types.h
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

#include <array>
#include <cstddef>
#include <string_view>

namespace Electux::App::Model::Channel {

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Enumeration of channel operational modes.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ChannelMode : int {
        Unknown = -1,
        Toggle = 0,
        Timer,
        Count
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Structure containing information about a channel operational mode.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct ChannelModeInfo {
        ChannelMode mode;
        std::string_view configKey;
        std::string_view displayName;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Array of channel mode descriptors.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr std::array<
        ChannelModeInfo, static_cast<size_t>(ChannelMode::Count)>
        cChannelModeDescriptors{
            {{ChannelMode::Toggle, "toggle", "Toggle Mode"},
             {ChannelMode::Timer, "timer", "Timer Mode"}}
        };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Converts a ChannelMode to its configuration key string.
    /// @param mode The ChannelMode to convert.
    /// @return The configuration key string for the given ChannelMode.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr std::string_view toConfigString(ChannelMode mode) {
        for (const auto &desc : cChannelModeDescriptors) {
            if (desc.mode == mode)
                return desc.configKey;
        }
        return "unknown";
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Converts a configuration key string to its ChannelMode.
    /// @param key The configuration key string to convert.
    /// @return The ChannelMode for the given configuration key.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr ChannelMode fromConfigString(std::string_view key) {
        for (const auto &desc : cChannelModeDescriptors) {
            if (desc.configKey == key)
                return desc.mode;
        }
        return ChannelMode::Unknown;
    }

} // namespace Electux::App::Model::Channel
