////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_device_resolver.h
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

#include <giomm.h>
#include <glibmm.h>
#include <string>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BluezDeviceResolver
    /// @brief Utility class to parse and resolve BlueZ D-Bus object paths.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BluezDeviceResolver {
      public:
        BluezDeviceResolver() = delete;
        ~BluezDeviceResolver() = delete;

        static Glib::ustring findDevicePath(
            const Glib::VariantContainerBase &objectsBase, 
            const std::string &address
        );

        static bool findGattPaths(
            const Glib::VariantContainerBase &objectsBase,
            const Glib::ustring &devicePath,
            const std::string &serviceUuid,
            const std::string &rxUuid,
            const std::string &txUuid,
            Glib::ustring &rxPath,
            Glib::ustring &txPath
        );
    };
} // namespace Electux::App::Com
