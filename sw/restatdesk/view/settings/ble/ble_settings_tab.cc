////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_settings_tab.cc
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

#include <string>
#include <view/settings/ble/ble_settings_tab.h>

namespace {
    constexpr std::string_view cSettingsBleAddressLabel{"BLE Device Address / Name"};
    constexpr std::string_view cSettingsBleServiceUuidLabel{"Service UUID"};
    constexpr std::string_view cSettingsBleRxUuidLabel{"RX Characteristic UUID"};
    constexpr std::string_view cSettingsBleTxUuidLabel{"TX Characteristic UUID"};
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Model;

BleSettingsTab::BleSettingsTab() : Gtk::Box(Gtk::Orientation::VERTICAL) {
    m_labelAddress.set_label(cSettingsBleAddressLabel.data());
    append(m_labelAddress);
    append(m_entryAddress);

    m_labelServiceUuid.set_label(cSettingsBleServiceUuidLabel.data());
    append(m_labelServiceUuid);
    append(m_entryServiceUuid);

    m_labelRxUuid.set_label(cSettingsBleRxUuidLabel.data());
    append(m_labelRxUuid);
    append(m_entryRxUuid);

    m_labelTxUuid.set_label(cSettingsBleTxUuidLabel.data());
    append(m_labelTxUuid);
    append(m_entryTxUuid);
}

void BleSettingsTab::updateData(const IModel &config) {
    auto addrKey = config.toString(ModelBleKey::Address);
    m_entryAddress.set_text(config.getEntity(addrKey).data());

    auto serviceKey = config.toString(ModelBleKey::ServiceUuid);
    m_entryServiceUuid.set_text(config.getEntity(serviceKey).data());

    auto rxKey = config.toString(ModelBleKey::RxUuid);
    m_entryRxUuid.set_text(config.getEntity(rxKey).data());

    auto txKey = config.toString(ModelBleKey::TxUuid);
    m_entryTxUuid.set_text(config.getEntity(txKey).data());
}

void BleSettingsTab::getData(IModel &config) {
    auto addrKey = config.toString(ModelBleKey::Address);
    config.update(addrKey, m_entryAddress.get_text().raw());

    auto serviceKey = config.toString(ModelBleKey::ServiceUuid);
    config.update(serviceKey, m_entryServiceUuid.get_text().raw());

    auto rxKey = config.toString(ModelBleKey::RxUuid);
    config.update(rxKey, m_entryRxUuid.get_text().raw());

    auto txKey = config.toString(ModelBleKey::TxUuid);
    config.update(txKey, m_entryTxUuid.get_text().raw());
}
