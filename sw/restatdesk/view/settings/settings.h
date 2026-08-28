////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings.h
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

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/window.h>
#include <sigc++/sigc++.h>
#include <view/settings/general/general_settings_tab.h>
#include <view/settings/isettings_view.h>
#include <view/settings/log/log_settings_tab.h>
#include <view/settings/serial/serial_settings_tab.h>
#include <view/settings/tcp/tcp_settings_tab.h>
#include <view/settings/ble/ble_settings_tab.h>
#include <view/settings_setup.h>

namespace Electux::App::View::Settings {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppSettings
    /// @brief Application settings window definition.
    ///
    /// Manages the UI for configuring settings, delegating tab rendering
    /// and data binding to SerialSettingsTab and LogSettingsTab.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppSettings : public Gtk::Window, public ISettingsView {
      public:
        explicit AppSettings();
        virtual ~AppSettings() override = default;

        AppSettings(const AppSettings &) = delete;
        AppSettings &operator=(const AppSettings &) = delete;

        SigSetup setupChanged() override;
        void setSettingsSetup(const SettingsSetup &setup) override;
        void getUiData() override;
        void updateUiData() override;

        void show() override;
        void hide() override;

      protected:
        void mapping();
        void onButtonOkClicked();
        void onButtonCancelClicked();

      private:
        SettingsSetup m_setup{};
        SigSetup m_setupSignal{};

        Gtk::Box m_boxRoot{};
        Gtk::Notebook m_notebook{};
        GeneralSettingsTab m_generalTab{};
        SerialSettingsTab m_serialTab{};
        TcpSettingsTab m_tcpTab{};
        BleSettingsTab m_bleTab{};
        LogSettingsTab m_logTab{};
        Gtk::Grid m_buttonBox{};

        Gtk::Button m_buttonOk{};
        Gtk::Button m_buttonCancel{};
    };
} // namespace Electux::App::View::Settings
