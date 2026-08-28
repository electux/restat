////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// switchable_com.cc
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

#include <com/com_types.h>
#include <com/switchable_com.h>
#include <iostream>

namespace Electux::App::Com {
    namespace {
        constexpr std::string_view cTcpSwitchMsg{"Switched communication channel to TCP/IP."};
        constexpr std::string_view cBleSwitchMsg{"Switched communication channel to BLE."};
        constexpr std::string_view cSerialSwitchMsg{"Switched communication channel to Serial Port."};
    } // namespace
    SwitchableCom::SwitchableCom(
        bool verbose,
        std::unique_ptr<ICom> serialCom,
        std::unique_ptr<ICom> tcpCom,
        std::unique_ptr<ICom> bleCom
    )
        : m_verbose(verbose),
          m_serialCom(std::move(serialCom)),
          m_tcpCom(std::move(tcpCom)),
          m_bleCom(std::move(bleCom)),
          m_activeCom(m_serialCom.get()) {}

    bool SwitchableCom::open() {
        if (m_activeCom) {
            return m_activeCom->open();
        }
        return false;
    }

    bool SwitchableCom::close() {
        if (m_activeCom) {
            return m_activeCom->close();
        }
        return false;
    }

    bool SwitchableCom::isOpen() const {
        if (m_activeCom) {
            return m_activeCom->isOpen();
        }
        return false;
    }

    void SwitchableCom::read(std::vector<uint8_t> &data, size_t len) {
        if (m_activeCom) {
            m_activeCom->read(data, len);
        }
    }

    void SwitchableCom::write(const std::vector<uint8_t> &data) {
        if (m_activeCom) {
            m_activeCom->write(data);
        }
    }

    void SwitchableCom::setComType(const std::string &type) {
        if (type == toConfigString(ComType::Tcp)) {
            if (m_activeCom != m_tcpCom.get()) {
                close();
                m_activeCom = m_tcpCom.get();
                if (m_verbose) {
                    std::cout << cTcpSwitchMsg << std::endl;
                }
            }
        } else if (type == toConfigString(ComType::Ble)) {
            if (m_activeCom != m_bleCom.get()) {
                close();
                m_activeCom = m_bleCom.get();
                if (m_verbose) {
                    std::cout << cBleSwitchMsg << std::endl;
                }
            }
        } else {
            if (m_activeCom != m_serialCom.get()) {
                close();
                m_activeCom = m_serialCom.get();
                if (m_verbose) {
                    std::cout << cSerialSwitchMsg << std::endl;
                }
            }
        }
    }

    ICom *SwitchableCom::getActiveCom() const { return m_activeCom; }

    ICom *SwitchableCom::getSerialCom() const { return m_serialCom.get(); }

    ICom *SwitchableCom::getTcpCom() const { return m_tcpCom.get(); }

    ICom *SwitchableCom::getBleCom() const { return m_bleCom.get(); }
} // namespace Electux::App::Com
