////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// application.h
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

#include <gtkmm/application.h>
#include <memory>

namespace Electux::App {
    class IAppController;

    namespace Model {
        class SettingsSetup;
    }

    namespace View {
        class IHomeView;
        namespace Settings {
            class ISettingsView;
        }
        namespace Help {
            class IHelpView;
        }
        namespace About {
            class IAboutView;
        }
    } // namespace View

    using SettingsSetup = Model::SettingsSetup;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class EntryApplication
    /// @brief Entry point for application and main application class.
    ///
    /// Manages the application lifecycle, signal mapping, and coordinates
    /// between the configuration manager and the various UI views.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class EntryApplication : public Gtk::Application {
      public:
        explicit EntryApplication(bool verbose = false);
        ~EntryApplication() override;

        static Glib::RefPtr<EntryApplication> create(bool verbose = false);

      protected:
        void on_startup() override;
        void on_activate() override;
        void on_shutdown() override;

      private:
        void mapping();
        void onActionSettings();
        void onActionDoc();
        void onActionAbout();
        void onActionQuit();
        void onActionCmdAllOn();
        void onActionCmdAllOff();
        void onActionCmdAllStat();
        void onActionCmdSysReset();
        void onActionCmdSysId();
        void onActionCmdSysVersion();
        void onActionCmdExecutePlan();
        bool onHandleClose();
        void onSetupChanged(const SettingsSetup &setup);

        bool m_verbose{false};
        std::unique_ptr<IAppController> m_controller;
        std::unique_ptr<View::IHomeView> m_home;
        std::unique_ptr<View::Settings::ISettingsView> m_settings;
        std::unique_ptr<View::Help::IHelpView> m_help;
        std::unique_ptr<View::About::IAboutView> m_about;
    };
} // namespace Electux::App
