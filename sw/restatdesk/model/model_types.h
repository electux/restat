////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// model_types.h
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

namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum ModelControlKey
    /// @brief Defines valid configuration keys for the control system.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ModelControlKey : uint8_t {
        Enable = 0, ///< Key for enabling/disabling control features
        Mode,       ///< Key for setting the operational mode
        Toggle,     ///< Key for toggle-based control states
        Timer,      ///< Key for timer duration settings
        TimerEnable ///< Key for enabling/disabling timer functionality
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum ModelLogKey
    /// @brief Defines valid configuration keys for the logging system.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ModelLogKey : uint8_t {
        FilePath = 0, ///< Key for the log file destination path
        LogLevel      ///< Key for the verbosity level setting
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum ModelSerialKey
    /// @brief Defines valid configuration keys for serial communication.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ModelSerialKey : uint8_t {
        Device = 0, ///< Key for serial device path (e.g., /dev/ttyUSB0)
        Baud,       ///< Key for baud rate setting
        Data,       ///< Key for data bits setting
        Parity,     ///< Key for parity setting
        Stop,       ///< Key for stop bits setting
        Flow        ///< Key for flow control setting
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum ModelGeneralKey
    /// @brief Defines valid configuration keys for general settings
    /// (communication mode, TCP).
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ModelGeneralKey : uint8_t {
        ComType = 0, ///< Key for communication type ("serial" or "tcp")
        TcpIp,       ///< Key for TCP IP Address
        TcpPort      ///< Key for TCP Port
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @enum ModelBleKey
    /// @brief Defines valid configuration keys for BLE settings.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class ModelBleKey : uint8_t {
        Address = 0,       ///< BLE device address or name
        ServiceUuid,       ///< BLE service UUID
        RxUuid,            ///< BLE RX characteristic UUID
        TxUuid             ///< BLE TX characteristic UUID
    };
} // namespace Electux::App::Model
