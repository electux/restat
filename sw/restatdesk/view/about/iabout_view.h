////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iabout_view.h
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

namespace Electux::App::View::About {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IAboutView
    /// @brief Interface defining the contract for the about/credits view.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IAboutView {
      public:
        virtual ~IAboutView() = default;

        virtual void show() = 0;
    };
} // namespace Electux::App::View::About
