////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_settings_tab.h
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
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <model/imodel.h>

namespace Electux::App::View::Settings {
    class SerialSettingsTab : public Gtk::Box {
      public:
        explicit SerialSettingsTab();
        virtual ~SerialSettingsTab() override = default;

        SerialSettingsTab(const SerialSettingsTab &) = delete;
        SerialSettingsTab &operator=(const SerialSettingsTab &) = delete;

        void updateData(const Electux::App::Model::IModel &config);
        void getData(Electux::App::Model::IModel &config);

      private:
        Gtk::Label m_labelSerialPath;
        Gtk::Entry m_entrySerialPath;
        Gtk::Label m_labelSerialBaud;
        Gtk::ComboBoxText m_comboSerialBaud;
        Gtk::Label m_labelSerialData;
        Gtk::ComboBoxText m_comboSerialData;
        Gtk::Label m_labelSerialParity;
        Gtk::ComboBoxText m_comboSerialParity;
        Gtk::Label m_labelSerialStop;
        Gtk::ComboBoxText m_comboSerialStop;
        Gtk::Label m_labelSerialFlowControl;
        Gtk::ComboBoxText m_comboSerialFlowControl;
    };
} // namespace Electux::App::View::Settings
