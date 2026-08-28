////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// about.h
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

#include <gtkmm/aboutdialog.h>
#include <view/about/iabout_view.h>

namespace Electux::App::View::About {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppAbout
    /// @brief About view dialog definition for the restatdesk application.
    ///
    /// Displays application metadata including version, copyright, license,
    /// and contributor information using the standard Gtk::AboutDialog.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppAbout : public Gtk::AboutDialog, public IAboutView {
      public:
        explicit AppAbout();
        virtual ~AppAbout() override = default;

        void show() override;
    };
} // namespace Electux::App::View::About
