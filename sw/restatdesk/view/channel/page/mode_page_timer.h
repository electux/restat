////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_timer.h
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
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/togglebutton.h>
#include <model/channel_state.h>
#include <sigc++/sigc++.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class TimerModePage
    /// @brief ModePage implementation for Timer Mode, inheriting from Gtk::Box.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class TimerModePage : public Gtk::Box {
      public:
        explicit TimerModePage(size_t index);
        virtual ~TimerModePage() override = default;

        TimerModePage(const TimerModePage &) = delete;
        TimerModePage &operator=(const TimerModePage &) = delete;
        TimerModePage(TimerModePage &&) = delete;
        TimerModePage &operator=(TimerModePage &&) = delete;

        void updateState(const ChannelState &state);
        void getState(ChannelState &state) const;
        sigc::signal<void()>& signal_changed() { return m_signalChanged; }

      private:
        void onTimerValueChanged();
        void onTimerToggleClicked();

        size_t m_index;
        Gtk::Label m_timerLabel;
        Gtk::SpinButton m_timerSpin;
        Gtk::ToggleButton m_timerToggleBtn;
        Gtk::ProgressBar m_progressBar;
        Gtk::Label m_descLabel;
        sigc::signal<void()> m_signalChanged;
    };
} // namespace Electux::App::View
