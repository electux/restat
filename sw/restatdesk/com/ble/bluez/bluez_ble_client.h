////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_ble_client.h
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
#include <vector>
#include <functional>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BluezBleClient
    /// @brief Low-level BlueZ D-Bus proxy interactions for BLE devices.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BluezBleClient {
      public:
        using NotificationCallback = std::function<void(const std::vector<uint8_t> &)>;

        BluezBleClient(
            const std::string &address,
            const std::string &serviceUuid,
            const std::string &rxUuid,
            const std::string &txUuid,
            bool verbose = false
        );
        ~BluezBleClient();

        BluezBleClient(const BluezBleClient &) = delete;
        BluezBleClient &operator=(const BluezBleClient &) = delete;

        bool connect(NotificationCallback callback);
        bool disconnect();
        bool isConnected() const;

        void write(const std::vector<uint8_t> &data);

      private:
        void onPropertiesChanged(
            const Glib::RefPtr<Gio::DBus::Connection>& connection,
            const Glib::ustring& sender_name,
            const Glib::ustring& object_path,
            const Glib::ustring& interface_name,
            const Glib::ustring& signal_name,
            const Glib::VariantContainerBase& parameters
        );

        std::string m_address;
        std::string m_serviceUuid;
        std::string m_rxUuid;
        std::string m_txUuid;

        bool m_connected;
        bool m_verbose;
        Glib::RefPtr<Gio::DBus::Connection> m_connection;
        Glib::ustring m_devicePath;
        Glib::ustring m_rxCharPath;
        Glib::ustring m_txCharPath;
        guint m_subscriptionId;

        NotificationCallback m_notificationCallback;
    };
} // namespace Electux::App::Com
