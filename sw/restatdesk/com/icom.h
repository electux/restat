////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// icom.h
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
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Com
/// @brief Namespace for application communication components
namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ICom
    /// @brief Interface for communication implementations.
    ///
    /// Defines the contract for managing com port lifecycle (open/close),
    /// configuration and data exchange (read/write).
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ICom {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor for the ICom interface.
        /// Ensures proper resource cleanup in derived communication classes.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        inline virtual ~ICom() noexcept = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Opens the communication channel.
        /// @return True if the channel was successfully opened, false
        /// otherwise. Implementation should handle the system call to acquire
        /// the device.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool open() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Closes the communication channel.
        /// @return True if the channel was successfully closed, false
        /// otherwise. Implementation should ensure buffers are flushed and
        /// resources are properly released.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool close() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Checks if the communication channel is currently open.
        /// @return True if the channel is open, false otherwise.
        /// Implementation should query the underlying serial port state.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool isOpen() const = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Reads data from the communication channel.
        /// @param data Vector buffer where the received bytes will be stored.
        /// @param len The number of bytes to read before returning.
        /// Implementation should block until 'len' bytes are received or a
        /// timeout occurs, and handle any necessary buffering or error
        /// conditions.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void read(std::vector<uint8_t> &data, size_t len) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Writes data to the communication channel.
        /// @param data Vector containing the sequence of bytes to be
        /// transmitted. Implementation should handle the system call to send
        /// data through the device and ensure that all bytes are transmitted
        /// successfully, or handle any errors that may occur during
        /// transmission.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void write(const std::vector<uint8_t> &data) = 0;
    };
} // namespace Electux::App::Com
