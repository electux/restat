////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iserial.h
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

#include <com/serial/serialw/ilib.h>
#include <cstdint>
#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Com
/// @brief Namespace for application communication components
namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @struct SerialParams
    /// @brief Configuration structure for serial port parameters.
    ///
    /// This structure aggregates all necessary settings required to initialize
    /// and configure a serial communication session.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    struct SerialParams {
        std::string device; ///< Path to the serial port device
        BaudRate baud;      ///< Transmission speed (Baud rate)
        CharacterSize data; ///< Number of data bits per character
        Parity parity;      ///< Parity error-checking scheme
        StopBits stop;      ///< Number of stop bits to indicate end
        FlowControl flow;   ///< Hardware or software flow control method
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ISerial
    /// @brief Interface for serial communication implementations.
    ///
    /// Defines the contract for configuring serial port parameters and
    /// provides utility methods to convert between LibSerial enums and
    /// generic numeric types for easier configuration handling.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ISerial {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor for the ISerial interface.
        /// Ensures proper resource cleanup in derived serial communication
        /// classes.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        inline virtual ~ISerial() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the serial port with specific parameters.
        /// @param params Reference to SerialParams structure (configuration).
        /// @return True if setup was successful, false otherwise.
        /// Implementation should apply the provided settings to the underlying
        /// serial port, returning success status based on the outcome.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool setup(const SerialParams &params) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the serial port device file path.
        /// @param device Path to the serial port device.
        /// Implementation should apply the provided settings to the underlying
        /// serial port.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setDevice(const std::string &device) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the baud rate for the serial port.
        /// @param baudRate The desired baud rate.
        /// Implementation should call the underlying serial port method to
        /// apply the baud rate setting.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBaudRate(BaudRate baudRate) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the character size for the serial port.
        /// @param characterSize The desired character size.
        /// Implementation should call the underlying serial port method to
        /// apply the character size setting.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setCharacterSize(CharacterSize characterSize) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the parity mode for the serial port.
        /// @param parity The desired parity mode.
        /// Implementation should call the underlying serial port method to
        /// apply the parity setting.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setParity(Parity parity) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the number of stop bits for the serial port.
        /// @param stopBits The desired number of stop bits.
        /// Implementation should call the underlying serial port method to
        /// apply the stop bits setting.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setStopBits(StopBits stopBits) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the flow control mode for the serial port.
        /// @param flowControl The desired flow control mode.
        /// Implementation should call the underlying serial port method to
        /// apply the flow control setting.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setFlowControl(FlowControl flowControl) = 0;
    };
} // namespace Electux::App::Com
