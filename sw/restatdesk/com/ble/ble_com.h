////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_com.h
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
#include <com/ble/ible.h>
#include <com/ble/bluez/bluez_ble_client.h>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BleCom
    /// @brief Implementation of BLE communication using BluezBleClient.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BleCom : public ICom, public IBle {
      public:
        explicit BleCom(bool verbose = false);
        ~BleCom() noexcept override;

        BleCom(const BleCom &) = delete;
        BleCom &operator=(const BleCom &) = delete;

        // ICom overrides
        bool open() override;
        bool close() override;
        bool isOpen() const override;
        void read(std::vector<uint8_t> &data, size_t len) override;
        void write(const std::vector<uint8_t> &data) override;

        // IBle overrides
        void setBleAddress(const std::string &address) override;
        void setServiceUuid(const std::string &uuid) override;
        void setRxUuid(const std::string &uuid) override;
        void setTxUuid(const std::string &uuid) override;

      private:
        void onNotificationReceived(const std::vector<uint8_t> &data);

        std::string m_address;
        std::string m_serviceUuid;
        std::string m_rxUuid;
        std::string m_txUuid;

        bool m_verbose;
        std::unique_ptr<BluezBleClient> m_client;

        std::vector<uint8_t> m_readBuffer;
        mutable std::mutex m_bufferMutex;
        std::condition_variable m_bufferCv;
    };
} // namespace Electux::App::Com
