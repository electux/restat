////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// com_types.h
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

namespace Electux::App::Com {

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Enumeration of communication types.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ComType : size_t { Serial = 0, Tcp, Ble, Count };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Structure containing information about a communication type.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct ComTypeInfo {
        ComType type;
        std::string_view configKey;
        std::string_view displayName;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Array of communication type descriptors.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr std::array<
        ComTypeInfo, static_cast<size_t>(ComType::Count)>
        cComTypeDescriptors{
            {{ComType::Serial, "serial", "Serial Port"},
             {ComType::Tcp, "tcp", "TCP/IP Connection"},
             {ComType::Ble, "ble", "BLE Connection"}}
        };

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Converts a ComType to its configuration key string.
    /// @param type The ComType to convert.
    /// @return The configuration key string for the given ComType.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr std::string_view toConfigString(ComType type) {
        for (const auto &desc : cComTypeDescriptors) {
            if (desc.type == type)
                return desc.configKey;
        }
        return cComTypeDescriptors[0].configKey;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Converts a configuration key string to its ComType.
    /// @param key The configuration key string to convert.
    /// @return The ComType for the given configuration key.
    ////////////////////////////////////////////////////////////////////////////////////////////////
    inline constexpr ComType fromConfigString(std::string_view key) {
        for (const auto &desc : cComTypeDescriptors) {
            if (desc.configKey == key)
                return desc.type;
        }
        return ComType::Serial;
    }

} // namespace Electux::App::Com
