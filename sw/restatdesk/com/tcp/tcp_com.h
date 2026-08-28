////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com.h
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

#include <com/icom.h>
#include <com/tcp/itcp.h>
#include <string>
#include <vector>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class TcpCom
    /// @brief Implementation of TCP/IP communication using raw BSD sockets.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class TcpCom : public ICom, public ITcp {
      public:
        explicit TcpCom(bool verbose = false);
        ~TcpCom() noexcept override;

        TcpCom(const TcpCom &) = delete;
        TcpCom &operator=(const TcpCom &) = delete;

        // ICom overrides
        bool open() override;
        bool close() override;
        bool isOpen() const override;
        void read(std::vector<uint8_t> &data, size_t len) override;
        void write(const std::vector<uint8_t> &data) override;

        // ITcp overrides
        void setIpAddress(const std::string &ip) override;
        void setPort(uint16_t port) override;

      private:
        std::string m_ip;
        uint16_t m_port;
        int m_socketFd;
        bool m_verbose;
    };
} // namespace Electux::App::Com
