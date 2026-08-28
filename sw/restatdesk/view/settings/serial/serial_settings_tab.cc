////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_settings_tab.cc
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

#include <com/serial/serial_com_params.h>
#include <string>
#include <view/settings/serial/serial_settings_tab.h>

namespace {
    constexpr std::string_view cSettingsSerialPath{"Device port"};
    constexpr std::string_view cSettingsSerialBaud{"Baud rate"};
    constexpr std::string_view cSettingsSerialData{"Data bits"};
    constexpr std::string_view cSettingsSerialParity{"Parity"};
    constexpr std::string_view cSettingsSerialStop{"Stop bits"};
    constexpr std::string_view cSettingsSerialFlowControl{"Flow control"};
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Model;
using namespace Electux::App::Com::SerialComConstants;

SerialSettingsTab::SerialSettingsTab() : Gtk::Box(Gtk::Orientation::VERTICAL) {
    m_labelSerialPath.set_label(cSettingsSerialPath.data());
    append(m_labelSerialPath);
    append(m_entrySerialPath);

    m_labelSerialBaud.set_label(cSettingsSerialBaud.data());
    append(m_labelSerialBaud);
    for (const auto &rate : cComBaudRates) {
        m_comboSerialBaud.append(std::string(rate));
    }
    append(m_comboSerialBaud);

    m_labelSerialData.set_label(cSettingsSerialData.data());
    append(m_labelSerialData);
    for (const auto &data : cComDataBits) {
        m_comboSerialData.append(std::string(data));
    }
    append(m_comboSerialData);

    m_labelSerialParity.set_label(cSettingsSerialParity.data());
    append(m_labelSerialParity);
    for (const auto &parity : cComParities) {
        m_comboSerialParity.append(std::string(parity));
    }
    append(m_comboSerialParity);

    m_labelSerialStop.set_label(cSettingsSerialStop.data());
    append(m_labelSerialStop);
    for (const auto &stop : cComStopBits) {
        m_comboSerialStop.append(std::string(stop));
    }
    append(m_comboSerialStop);

    m_labelSerialFlowControl.set_label(cSettingsSerialFlowControl.data());
    append(m_labelSerialFlowControl);
    for (const auto &flow : cComFlowControls) {
        m_comboSerialFlowControl.append(std::string(flow));
    }
    append(m_comboSerialFlowControl);
}

void SerialSettingsTab::updateData(const IModel &config) {
    auto pathKey = config.toString(ModelSerialKey::Device);
    m_entrySerialPath.set_text(config.getEntity(pathKey).data());

    auto baudKey = config.toString(ModelSerialKey::Baud);
    auto baudValue = std::stoi(config.getEntity(baudKey).data());
    m_comboSerialBaud.set_active(baudValue);

    auto dataKey = config.toString(ModelSerialKey::Data);
    auto dataValue = std::stoi(config.getEntity(dataKey).data());
    m_comboSerialData.set_active(dataValue);

    auto parityKey = config.toString(ModelSerialKey::Parity);
    auto parityValue = std::stoi(config.getEntity(parityKey).data());
    m_comboSerialParity.set_active(parityValue);

    auto stopKey = config.toString(ModelSerialKey::Stop);
    auto stopValue = std::stoi(config.getEntity(stopKey).data());
    m_comboSerialStop.set_active(stopValue);

    auto flowKey = config.toString(ModelSerialKey::Flow);
    auto flowValue = std::stoi(config.getEntity(flowKey).data());
    m_comboSerialFlowControl.set_active(flowValue);
}

void SerialSettingsTab::getData(IModel &config) {
    auto pathKey = config.toString(ModelSerialKey::Device);
    config.update(pathKey, m_entrySerialPath.get_text().raw());

    auto baudKey = config.toString(ModelSerialKey::Baud);
    config.update(
        baudKey, std::to_string(m_comboSerialBaud.get_active_row_number())
    );

    auto dataKey = config.toString(ModelSerialKey::Data);
    config.update(
        dataKey, std::to_string(m_comboSerialData.get_active_row_number())
    );

    auto parityKey = config.toString(ModelSerialKey::Parity);
    config.update(
        parityKey, std::to_string(m_comboSerialParity.get_active_row_number())
    );

    auto stopKey = config.toString(ModelSerialKey::Stop);
    config.update(
        stopKey, std::to_string(m_comboSerialStop.get_active_row_number())
    );

    auto flowKey = config.toString(ModelSerialKey::Flow);
    config.update(
        flowKey,
        std::to_string(m_comboSerialFlowControl.get_active_row_number())
    );
}
