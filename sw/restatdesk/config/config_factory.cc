////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_factory.cc
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

#include <config/config_factory.h>
#include <config/config_manager.h>
#include <model/imodel.h>

namespace Electux::App::Config {
    std::unique_ptr<IConfig> createConfigManager(
        std::unique_ptr<Electux::App::Model::IModel> config,
        bool verbose
    ) {
        return std::make_unique<ConfigManager>(std::move(config), "", verbose);
    }
} // namespace Electux::App::Config
