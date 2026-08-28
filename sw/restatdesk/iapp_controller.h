////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iapp_controller.h
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

#include <sigc++/sigc++.h>
#include <string>

namespace Electux::App {
    namespace Model {
        class IModel;
        class SettingsSetup;
    } // namespace Model

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IAppController
    /// @brief Interface defining the contract for the application business
    /// logic coordinator.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IAppController {
      public:
        virtual ~IAppController() = default;

        virtual void startup() = 0;
        virtual void shutdown() = 0;

        virtual const Model::IModel &getModel() const = 0;

        virtual void onSetupChanged(const Model::SettingsSetup &setup) = 0;

        virtual void executePlan() = 0;

        virtual sigc::signal<void(const std::string&)> signal_data_received() = 0;

        virtual void turnOnAllChannels() = 0;
        virtual void turnOffAllChannels() = 0;
        virtual void requestAllChannelsStatus() = 0;
        virtual void resetSystem() = 0;
        virtual void requestBoardId() = 0;
        virtual void requestVersion() = 0;
    };
} // namespace Electux::App
