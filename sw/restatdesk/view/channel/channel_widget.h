////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// channel_widget.h
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

#include <gtkmm/frame.h>
#include <gtkmm/box.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/stack.h>
#include <model/channel_state.h>
#include <sigc++/sigc++.h>
#include <view/channel/page/mode_page_toggle.h>
#include <view/channel/page/mode_page_timer.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ChannelWidget
    /// @brief A self-contained UI component managing a single communication channel's controls.
    ///
    /// This widget encapsulates all UI elements for a single channel, leveraging Gtk::Stack
    /// to switch between mode-specific control panels dynamically.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ChannelWidget : public Gtk::Frame {
      public:
        explicit ChannelWidget(size_t index);
        virtual ~ChannelWidget() override = default;

        ChannelWidget(const ChannelWidget &) = delete;
        ChannelWidget &operator=(const ChannelWidget &) = delete;
        ChannelWidget(ChannelWidget &&) = delete;
        ChannelWidget &operator=(ChannelWidget &&) = delete;

        void updateState(const ChannelState &state);
        ChannelState getState() const;
        void setLedState(bool on);

        sigc::signal<void()>& signal_changed() { return m_signalChanged; }

      private:
        void updateSensitivity();
        void onEnableToggled();
        void onModeChanged();
        void onChildPageChanged();

        size_t m_index;
        bool m_blockSignals{false};

        Gtk::Box m_mainBox;
        Gtk::Box m_headerBox;
        Gtk::Box m_led;
        Gtk::CheckButton m_enableBtn;
        Gtk::ComboBoxText m_modeCombo;

        Gtk::Stack m_stack;
        ToggleModePage m_pageToggle;
        TimerModePage m_pageTimer;

        sigc::signal<void()> m_signalChanged;
    };
} // namespace Electux::App::View
