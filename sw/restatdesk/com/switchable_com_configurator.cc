////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// switchable_com_configurator.cc
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
#include <com/switchable_com_configurator.h>
#include <model/imodel.h>
#include <string>

namespace Electux::App::Com {
    SwitchableComConfigurator::SwitchableComConfigurator(
        SwitchableCom *switchableCom,
        std::unique_ptr<IComConfigurator> serialConfigurator,
        std::unique_ptr<IComConfigurator> tcpConfigurator,
        std::unique_ptr<IComConfigurator> bleConfigurator
    )
        : m_switchableCom(switchableCom),
          m_serialConfigurator(std::move(serialConfigurator)),
          m_tcpConfigurator(std::move(tcpConfigurator)),
          m_bleConfigurator(std::move(bleConfigurator)) {}

    bool SwitchableComConfigurator::configure(
        const Model::IModel &model, ICom *comChannel
    ) {
        (void)comChannel; // Suppress unused parameter warning

        auto comTypeKey = model.toString(Model::ModelGeneralKey::ComType);
        std::string comType = model.getEntity(comTypeKey);

        m_switchableCom->setComType(comType);

        if (comType == toConfigString(ComType::Tcp)) {
            return m_tcpConfigurator->configure(
                model, m_switchableCom->getTcpCom()
            );
        } else if (comType == toConfigString(ComType::Ble)) {
            return m_bleConfigurator->configure(
                model, m_switchableCom->getBleCom()
            );
        } else {
            return m_serialConfigurator->configure(
                model, m_switchableCom->getSerialCom()
            );
        }
    }
} // namespace Electux::App::Com
