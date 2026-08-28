////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// general_settings_tab.cc
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

#include <com/com_types.h>
#include <string>
#include <view/settings/general/general_settings_tab.h>

namespace {
    constexpr std::string_view cSettingsComTypeLabel{"Connection type"};
} // namespace

using Electux::App::Com::cComTypeDescriptors;
using Electux::App::Com::ComType;
using Electux::App::Com::fromConfigString;
using Electux::App::Com::toConfigString;
using Electux::App::Model::IModel;
using Electux::App::Model::ModelGeneralKey;
using Electux::App::View::Settings::GeneralSettingsTab;

GeneralSettingsTab::GeneralSettingsTab()
    : Gtk::Box(Gtk::Orientation::VERTICAL) {
    m_labelComType.set_label(cSettingsComTypeLabel.data());
    append(m_labelComType);

    for (const auto &desc : cComTypeDescriptors) {
        m_comboComType.append(desc.displayName.data());
    }

    m_comboComType.set_active(0);
    append(m_comboComType);
}

void GeneralSettingsTab::updateData(const IModel &config) {
    auto comTypeKey = config.toString(ModelGeneralKey::ComType);
    auto value = config.getEntity(comTypeKey);

    ComType type = fromConfigString(value);
    m_comboComType.set_active(static_cast<int>(type));
}

void GeneralSettingsTab::getData(IModel &config) {
    auto comTypeKey = config.toString(ModelGeneralKey::ComType);
    int active = m_comboComType.get_active_row_number();

    if (active >= 0 && active < static_cast<int>(ComType::Count)) {
        ComType type = static_cast<ComType>(active);
        config.update(comTypeKey, std::string(toConfigString(type)));
    } else {
        config.update(comTypeKey, std::string(toConfigString(ComType::Serial)));
    }
}
