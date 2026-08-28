////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_settings_tab.h
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
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <model/imodel.h>

namespace Electux::App::View::Settings {
    class BleSettingsTab : public Gtk::Box {
      public:
        explicit BleSettingsTab();
        virtual ~BleSettingsTab() override = default;

        BleSettingsTab(const BleSettingsTab &) = delete;
        BleSettingsTab &operator=(const BleSettingsTab &) = delete;

        void updateData(const Electux::App::Model::IModel &config);
        void getData(Electux::App::Model::IModel &config);

      private:
        Gtk::Label m_labelAddress;
        Gtk::Entry m_entryAddress;
        Gtk::Label m_labelServiceUuid;
        Gtk::Entry m_entryServiceUuid;
        Gtk::Label m_labelRxUuid;
        Gtk::Entry m_entryRxUuid;
        Gtk::Label m_labelTxUuid;
        Gtk::Entry m_entryTxUuid;
    };
} // namespace Electux::App::View::Settings
