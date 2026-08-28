////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// isettings_view.h
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
#include <view/settings_setup.h>

namespace Electux::App::View::Settings {
    using SettingsSetup = Electux::App::Model::SettingsSetup;
    using SigSetup = sigc::signal<void(const SettingsSetup &)>;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ISettingsView
    /// @brief Interface defining the contract for the settings tab view.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ISettingsView {
      public:
        virtual ~ISettingsView() = default;

        virtual SigSetup setupChanged() = 0;
        virtual void setSettingsSetup(const SettingsSetup &setup) = 0;
        virtual void updateUiData() = 0;
        virtual void getUiData() = 0;

        virtual void show() = 0;
        virtual void hide() = 0;
    };
} // namespace Electux::App::View::Settings
