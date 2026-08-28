////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_params.h
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
/// @namespace Electux::App::Com::SerialComConstants
/// @brief Namespace for serial communication constants and definitions
namespace Electux::App::Com::SerialComConstants {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Baud Rate Parameters
    /// @{

    /// @brief Supported baud rate string representations
    constexpr std::string_view cComBaudRates[]{"110",   "300",    "600",
                                               "1200",  "2400",   "4800",
                                               "9600",  "19200",  "38400",
                                               "57600", "115200", "230400"};

    constexpr const uint32_t cComBaud110 = 0;     ///< Index for 110 baud
    constexpr const uint32_t cComBaud300 = 1;     ///< Index for 300 baud
    constexpr const uint32_t cComBaud600 = 2;     ///< Index for 600 baud
    constexpr const uint32_t cComBaud1200 = 3;    ///< Index for 1200 baud
    constexpr const uint32_t cComBaud2400 = 4;    ///< Index for 2400 baud
    constexpr const uint32_t cComBaud4800 = 5;    ///< Index for 4800 baud
    constexpr const uint32_t cComBaud9600 = 6;    ///< Index for 9600 baud
    constexpr const uint32_t cComBaud19200 = 7;   ///< Index for 19200 baud
    constexpr const uint32_t cComBaud38400 = 8;   ///< Index for 38400 baud
    constexpr const uint32_t cComBaud57600 = 9;   ///< Index for 57600 baud
    constexpr const uint32_t cComBaud115200 = 10; ///< Index for 115200 baud
    constexpr const uint32_t cComBaud230400 = 11; ///< Index for 230400 baud
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Data Bits Parameters
    /// @{

    /// @brief Supported data bits string representations
    constexpr std::string_view cComDataBits[]{"5", "6", "7", "8"};

    constexpr const uint32_t cComDataBits5 = 0; ///< Index for 5 data bits
    constexpr const uint32_t cComDataBits6 = 1; ///< Index for 6 data bits
    constexpr const uint32_t cComDataBits7 = 2; ///< Index for 7 data bits
    constexpr const uint32_t cComDataBits8 = 3; ///< Index for 8 data bits
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Parity Parameters
    /// @{

    /// @brief Supported parity mode string representations
    constexpr std::string_view cComParities[]{"Even", "Odd", "None"};

    constexpr const uint32_t cComParityEven = 0; ///< Index for even parity
    constexpr const uint32_t cComParityOdd = 1;  ///< Index for odd parity
    constexpr const uint32_t cComParityNone = 2; ///< Index for no parity
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Stop Bits Parameters
    /// @{

    /// @brief Supported stop bits string representations
    constexpr std::string_view cComStopBits[]{"1", "2"};

    constexpr const uint32_t cComStopBits1 = 0; ///< Index for 1 stop bit
    constexpr const uint32_t cComStopBits2 = 1; ///< Index for 2 stop bits
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Flow Control Parameters
    /// @{

    /// @brief Supported flow control string representations
    constexpr std::string_view cComFlowControls[]{
        "None", "Hardware", "Software"
    };

    constexpr const uint32_t cComFlowControlNone =
        0; ///< Index for no flow control
    constexpr const uint32_t cComFlowControlHw =
        1; ///< Index for hardware flow control
    constexpr const uint32_t cComFlowControlSw =
        2; ///< Index for software flow control
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Error Indicators
    /// @{

    /// @brief Value used to indicate an invalid or unsupported parameter
    constexpr const uint32_t cComInvalidParameter = 127;
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Electux::App::Com::SerialComConstants
