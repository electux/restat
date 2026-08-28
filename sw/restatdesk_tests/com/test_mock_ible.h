////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// test_mock_ible.h
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

#include <com/ble/ible.h>
#include <string>

namespace com::mock {
    class MockIBle : public Electux::App::Com::IBle {
      public:
        MockIBle() = default;
        ~MockIBle() override = default;

        void setBleAddress(const std::string &address) override {
            m_address = address;
        }

        void setServiceUuid(const std::string &uuid) override {
            m_serviceUuid = uuid;
        }

        void setRxUuid(const std::string &uuid) override {
            m_rxUuid = uuid;
        }

        void setTxUuid(const std::string &uuid) override {
            m_txUuid = uuid;
        }

        std::string m_address;
        std::string m_serviceUuid;
        std::string m_rxUuid;
        std::string m_txUuid;
    };
} // namespace com::mock
