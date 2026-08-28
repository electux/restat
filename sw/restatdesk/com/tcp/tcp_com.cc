////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com.cc
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

#include <arpa/inet.h>
#include <com/tcp/tcp_com.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Electux::App::Com;

namespace {
    constexpr std::string_view cDefaultIp{"127.0.0.1"};
    constexpr std::string_view cTcpComConstructorMsg{"TcpCom constructor called."};
    constexpr std::string_view cTcpComDestructorMsg{"TcpCom destructor called."};
    constexpr std::string_view cTcpOpenSocketError{"TcpCom open error: Failed to create socket."};
    constexpr std::string_view cTcpOpenAddrError{"TcpCom open error: Invalid address or Address not supported."};
    constexpr std::string_view cTcpOpenConnError{"TcpCom open error: Connection Failed."};
    constexpr std::string_view cTcpCloseMsg{"TcpCom connection closed."};
    constexpr std::string_view cTcpReadError{"TcpCom read: Connection lost or read error."};
    constexpr std::string_view cTcpWriteError{"TcpCom write: Connection lost or write error."};
    constexpr std::string_view cTcpWriteNotOpenError{"TcpCom write error: Connection is not open."};
    constexpr uint16_t cDefaultPort{5000};
} // namespace

TcpCom::TcpCom(bool verbose) : m_ip(cDefaultIp), m_port(cDefaultPort), m_socketFd(-1), m_verbose(verbose) {
    if (m_verbose) {
        std::cout << cTcpComConstructorMsg << std::endl;
    }
}

TcpCom::~TcpCom() noexcept {
    close();
    if (m_verbose) {
        std::cout << cTcpComDestructorMsg << std::endl;
    }
}

bool TcpCom::open() {
    if (isOpen()) {
        return true;
    }

    m_socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socketFd < 0) {
        std::cerr << cTcpOpenSocketError << std::endl;
        return false;
    }

    struct sockaddr_in serv_addr{};
    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);

    if (::inet_pton(AF_INET, m_ip.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr << cTcpOpenAddrError << std::endl;
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    if (::connect(
            m_socketFd, reinterpret_cast<struct sockaddr *>(&serv_addr), sizeof(serv_addr)
        ) < 0) {
        std::cerr << cTcpOpenConnError << std::endl;
        ::close(m_socketFd);
        m_socketFd = -1;
        return false;
    }

    if (m_verbose) {
        std::cout << "TcpCom connected successfully to " << m_ip << ":" << m_port
                  << std::endl;
    }
    return true;
}

bool TcpCom::close() {
    if (isOpen()) {
        ::close(m_socketFd);
        m_socketFd = -1;
        if (m_verbose) {
            std::cout << cTcpCloseMsg << std::endl;
        }
        return true;
    }
    return false;
}

bool TcpCom::isOpen() const { return m_socketFd != -1; }

void TcpCom::read(std::vector<uint8_t> &data, size_t len) {
    if (!isOpen()) {
        return;
    }

    data.resize(len);
    size_t totalRead = 0;
    while (totalRead < len) {
        ssize_t bytesRead =
            ::recv(m_socketFd, &data.at(totalRead), len - totalRead, 0);
        if (bytesRead <= 0) {
            std::cerr << cTcpReadError << std::endl;
            close();
            break;
        }
        totalRead += static_cast<size_t>(bytesRead);
    }
}

void TcpCom::write(const std::vector<uint8_t> &data) {
    if (!isOpen()) {
        std::cerr << cTcpWriteNotOpenError << std::endl;
        return;
    }

    size_t totalSent = 0;
    while (totalSent < data.size()) {
        ssize_t bytesSent = ::send(
            m_socketFd, &data.at(totalSent), data.size() - totalSent, 0
        );
        if (bytesSent <= 0) {
            std::cerr << cTcpWriteError << std::endl;
            close();
            break;
        }
        totalSent += static_cast<size_t>(bytesSent);
    }
}

void TcpCom::setIpAddress(const std::string &ip) { m_ip = ip; }

void TcpCom::setPort(uint16_t port) { m_port = port; }
