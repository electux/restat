////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_settings_tab.cc
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
#include <view/settings/tcp/tcp_settings_tab.h>

namespace {
    constexpr std::string_view cSettingsTcpIpLabel{"IP Address"};
    constexpr std::string_view cSettingsTcpPortLabel{"Port number"};
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Model;

TcpSettingsTab::TcpSettingsTab() : Gtk::Box(Gtk::Orientation::VERTICAL) {
    m_labelIpAddress.set_label(cSettingsTcpIpLabel.data());
    append(m_labelIpAddress);
    append(m_entryIpAddress);

    m_labelPort.set_label(cSettingsTcpPortLabel.data());
    append(m_labelPort);
    append(m_entryPort);
}

void TcpSettingsTab::updateData(const IModel &config) {
    auto ipKey = config.toString(ModelGeneralKey::TcpIp);
    m_entryIpAddress.set_text(config.getEntity(ipKey).data());

    auto portKey = config.toString(ModelGeneralKey::TcpPort);
    m_entryPort.set_text(config.getEntity(portKey).data());
}

void TcpSettingsTab::getData(IModel &config) {
    auto ipKey = config.toString(ModelGeneralKey::TcpIp);
    config.update(ipKey, m_entryIpAddress.get_text().raw());

    auto portKey = config.toString(ModelGeneralKey::TcpPort);
    config.update(portKey, m_entryPort.get_text().raw());
}
