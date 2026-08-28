////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// com_factory.cc
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

#include <com/com_factory.h>
#include <com/serial/serial_com.h>
#include <com/tcp/tcp_com.h>
#include <com/ble/ble_com.h>
#include <com/switchable_com.h>

namespace Electux::App::Com {
    std::unique_ptr<ICom> createSerialCom(bool verbose) {
        return std::make_unique<SerialCom>(verbose);
    }

    std::unique_ptr<ICom> createTcpCom(bool verbose) {
        return std::make_unique<TcpCom>(verbose);
    }

    std::unique_ptr<ICom> createBleCom(bool verbose) {
        return std::make_unique<BleCom>(verbose);
    }

    std::unique_ptr<ICom> createSwitchableCom(
        bool verbose,
        std::unique_ptr<ICom> serialCom,
        std::unique_ptr<ICom> tcpCom,
        std::unique_ptr<ICom> bleCom
    ) {
        return std::make_unique<SwitchableCom>(
            verbose,
            std::move(serialCom),
            std::move(tcpCom),
            std::move(bleCom)
        );
    }
} // namespace Electux::App::Com
