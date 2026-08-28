////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// itcp.h
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
#include <string>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ITcp
    /// @brief Interface for TCP communication configuration parameters.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ITcp {
      public:
        virtual ~ITcp() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the target IP Address for the TCP connection.
        /// @param ip The IP address.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setIpAddress(const std::string &ip) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the target port number for the TCP connection.
        /// @param port The port number.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPort(uint16_t port) = 0;
    };
} // namespace Electux::App::Com
