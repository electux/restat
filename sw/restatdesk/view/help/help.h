////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// help.h
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

#include <gtkmm/window.h>
#include <view/help/ihelp_view.h>

namespace Electux::App::View::Help {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppHelp
    /// @brief Help view window definition for application documentation.
    ///
    /// This window provides users with access to local documentation or
    /// help resources related to restatdesk functionality.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppHelp : public Gtk::Window, public IHelpView {
      public:
        explicit AppHelp();
        virtual ~AppHelp() override = default;

        void show() override;
    };
} // namespace Electux::App::View::Help
