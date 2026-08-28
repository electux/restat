////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com_configurator.cc
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

#include <com/icom.h>
#include <com/tcp/itcp.h>
#include <com/tcp/configurator/tcp_com_configurator.h>
#include <model/imodel.h>
#include <string>

namespace Electux::App::Com {
    TcpComConfigurator::TcpComConfigurator(ITcp *tcp) : m_tcp(tcp) {}

    bool TcpComConfigurator::configure(
        const Model::IModel &model, ICom *comChannel
    ) {
        if (m_tcp == nullptr || comChannel == nullptr) {
            return false;
        }

        auto ipKey = model.toString(Model::ModelGeneralKey::TcpIp);
        auto portKey = model.toString(Model::ModelGeneralKey::TcpPort);

        std::string ip = model.getEntity(ipKey);
        uint16_t port =
            static_cast<uint16_t>(std::stoul(model.getEntity(portKey)));

        m_tcp->setIpAddress(ip);
        m_tcp->setPort(port);

        return comChannel->open();
    }
} // namespace Electux::App::Com
