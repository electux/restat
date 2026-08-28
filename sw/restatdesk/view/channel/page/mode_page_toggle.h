////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_toggle.h
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
#include <gtkmm/togglebutton.h>
#include <gtkmm/progressbar.h>
#include <model/channel_state.h>
#include <sigc++/sigc++.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ToggleModePage
    /// @brief ModePage implementation for Toggle Mode, inheriting from Gtk::Box.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ToggleModePage : public Gtk::Box {
      public:
        explicit ToggleModePage(size_t index);
        virtual ~ToggleModePage() override = default;

        ToggleModePage(const ToggleModePage &) = delete;
        ToggleModePage &operator=(const ToggleModePage &) = delete;
        ToggleModePage(ToggleModePage &&) = delete;
        ToggleModePage &operator=(ToggleModePage &&) = delete;

        void updateState(const ChannelState &state);
        void getState(ChannelState &state) const;
        sigc::signal<void()>& signal_changed() { return m_signalChanged; }

      private:
        void onToggleClicked();

        size_t m_index;
        Gtk::ToggleButton m_toggleBtn;
        Gtk::Label m_descLabel;
        Gtk::ProgressBar m_progressBar;
        sigc::signal<void()> m_signalChanged;
    };
} // namespace Electux::App::View
