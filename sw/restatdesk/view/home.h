////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home.h
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

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <memory>
#include <vector>
#include <queue>
#include <mutex>
#include <glibmm/dispatcher.h>
#include <view/channel/channel_widget.h>
#include <view/ihome_view.h>
#include <view/settings_setup.h>

namespace Electux::App::View {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppHome
    /// @brief Home view window definition for the restatdesk application.
    ///
    /// Provides the main user interface for monitoring and controlling
    /// multiple channels, delegating to individual ChannelWidget components.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppHome : public Gtk::ApplicationWindow, public IHomeView {
      public:
        explicit AppHome();
        virtual ~AppHome() override = default;

        AppHome(const AppHome &) = delete;
        AppHome &operator=(const AppHome &) = delete;

        SigSettings controlChanged() override;
        void setControlSetup(const SettingsSetup &setup) override;
        void getUiData() override;
        void updateUiData() override;

        sigc::signal<void()>& signal_execute_plan() override { return m_signalExecutePlan; }

        void show() override;
        void hide() override;
        void connect_close_request(const sigc::slot<bool()> &slot) override;
        Gtk::Window &getGtkWindow() override;

        void postData(const std::string& data) override;

      private:
        void onChannelChanged(size_t index);
        void onDataReceivedDispatcher();
        void updateLedsFromMessage(const std::string &msg);

        SettingsSetup m_setup{};
        SigSettings m_controlSignal{};
        sigc::signal<void()> m_signalExecutePlan;

        Gtk::Box m_boxRoot{};
        Gtk::Box m_boxChannels{};
        Gtk::Box m_boxActions{};
        Gtk::Button m_btnExecutePlan;
        Gtk::ScrolledWindow m_scrolled_window{};
        Gtk::TextView m_textView{};
        std::vector<std::unique_ptr<ChannelWidget>> m_channelWidgets{};

        Glib::Dispatcher m_dispatcher{};
        std::queue<std::string> m_incomingDataQueue{};
        std::mutex m_mutex{};
    };
} // namespace Electux::App::View
