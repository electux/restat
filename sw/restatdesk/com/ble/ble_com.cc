////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_com.cc
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

#include <com/ble/ble_com.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace Electux::App::Com;

namespace {
    constexpr std::string_view cConstructorMsg{"BleCom constructor called."};
    constexpr std::string_view cDestructorMsg{"BleCom destructor called."};
    constexpr std::string_view cOpenSuccessMsg{"BleCom opened successfully."};
    constexpr std::string_view cCloseSuccessMsg{"BleCom closed successfully."};
    constexpr std::string_view cWriteError{"BleCom write error: Connection is not open."};
    constexpr std::chrono::seconds cReadTimeout{5};
} // namespace

BleCom::BleCom(bool verbose)
    : m_address(""),
      m_serviceUuid(""),
      m_rxUuid(""),
      m_txUuid(""),
      m_verbose(verbose),
      m_client(nullptr) {
    if (m_verbose) {
        std::cout << cConstructorMsg << std::endl;
    }
}

BleCom::~BleCom() noexcept {
    close();
    if (m_verbose) {
        std::cout << cDestructorMsg << std::endl;
    }
}

bool BleCom::open() {
    if (isOpen()) {
        return true;
    }

    m_client = std::make_unique<BluezBleClient>(m_address, m_serviceUuid, m_rxUuid, m_txUuid, m_verbose);
    
    auto callback = [this](const std::vector<uint8_t> &data) {
        onNotificationReceived(data);
    };

    if (m_client->connect(callback)) {
        if (m_verbose) {
            std::cout << cOpenSuccessMsg << std::endl;
        }
        return true;
    }

    m_client.reset();
    return false;
}

bool BleCom::close() {
    if (m_client) {
        m_client->disconnect();
        m_client.reset();
        if (m_verbose) {
            std::cout << cCloseSuccessMsg << std::endl;
        }
        return true;
    }
    return false;
}

bool BleCom::isOpen() const { 
    return m_client && m_client->isConnected(); 
}

void BleCom::read(std::vector<uint8_t> &data, size_t len) {
    if (!isOpen()) {
        return;
    }

    data.clear();
    std::unique_lock<std::mutex> lock(m_bufferMutex);
    bool success = m_bufferCv.wait_for(lock, cReadTimeout, [this, len]() {
        return m_readBuffer.size() >= len;
    });

    if (success) {
        data.assign(m_readBuffer.begin(), m_readBuffer.begin() + static_cast<std::vector<uint8_t>::difference_type>(len));
        m_readBuffer.erase(m_readBuffer.begin(), m_readBuffer.begin() + static_cast<std::vector<uint8_t>::difference_type>(len));
    } else {
        size_t toCopy = std::min(len, m_readBuffer.size());
        data.assign(m_readBuffer.begin(), m_readBuffer.begin() + static_cast<std::vector<uint8_t>::difference_type>(toCopy));
        m_readBuffer.erase(m_readBuffer.begin(), m_readBuffer.begin() + static_cast<std::vector<uint8_t>::difference_type>(toCopy));
    }
}

void BleCom::write(const std::vector<uint8_t> &data) {
    if (!isOpen()) {
        std::cerr << cWriteError << std::endl;
        return;
    }
    m_client->write(data);
}

void BleCom::setBleAddress(const std::string &address) { m_address = address; }

void BleCom::setServiceUuid(const std::string &uuid) { m_serviceUuid = uuid; }

void BleCom::setRxUuid(const std::string &uuid) { m_rxUuid = uuid; }

void BleCom::setTxUuid(const std::string &uuid) { m_txUuid = uuid; }

void BleCom::onNotificationReceived(const std::vector<uint8_t> &data) {
    std::lock_guard<std::mutex> lock(m_bufferMutex);
    m_readBuffer.insert(m_readBuffer.end(), data.begin(), data.end());
    m_bufferCv.notify_all();
}
