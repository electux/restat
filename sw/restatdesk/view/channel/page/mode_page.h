////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page.h
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

#include <model/channel_state.h>
#include <sigc++/sigc++.h>

namespace Electux::App::View {
    using ChannelState = Electux::App::Model::Channel::ChannelState;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ModePage
    /// @brief Pure interface for mode-specific pages inside ChannelWidget's stack.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ModePage {
      public:
        virtual ~ModePage() = default;

        virtual void updateState(const ChannelState &state) = 0;
        virtual void getState(ChannelState &state) const = 0;
        virtual sigc::signal<void()> signal_changed() = 0;
    };
} // namespace Electux::App::View
