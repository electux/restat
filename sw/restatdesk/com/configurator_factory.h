////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// configurator_factory.h
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
#include <com/icom_configurator.h>
#include <memory>

namespace Electux::App::Com {
    std::unique_ptr<IComConfigurator> createSerialConfigurator(ICom* com);
    std::unique_ptr<IComConfigurator> createTcpConfigurator(ICom* com);
    std::unique_ptr<IComConfigurator> createBleConfigurator(ICom* com);
    std::unique_ptr<IComConfigurator> createSwitchableConfigurator(
        ICom* com,
        std::unique_ptr<IComConfigurator> serialConfigurator,
        std::unique_ptr<IComConfigurator> tcpConfigurator,
        std::unique_ptr<IComConfigurator> bleConfigurator
    );
} // namespace Electux::App::Com
