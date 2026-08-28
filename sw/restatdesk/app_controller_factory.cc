////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller_factory.cc
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

#include <app_controller_factory.h>
#include <app_controller.h>

namespace Electux::App {
    std::unique_ptr<IAppController> createAppController(
        std::unique_ptr<Config::IConfig> configManager,
        std::unique_ptr<Com::ICom> comChannel,
        std::unique_ptr<Com::IComConfigurator> comConfigurator,
        std::unique_ptr<Logger::ILog> logger,
        std::unique_ptr<Command::ICommandFormatter> commandFormatter,
        std::unique_ptr<Command::IResponseProcessor> responseProcessor
    ) {
        return std::make_unique<AppController>(
            std::move(configManager),
            std::move(comChannel),
            std::move(comConfigurator),
            std::move(logger),
            std::move(commandFormatter),
            std::move(responseProcessor)
        );
    }
} // namespace Electux::App
