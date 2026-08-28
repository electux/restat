////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// log_settings_tab.cc
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

#include <log/log_level_params.h>
#include <string>
#include <view/settings/log/log_settings_tab.h>

namespace {
    constexpr std::string_view cSettingsLogPath{"Log file path"};
    constexpr std::string_view cSettingsLogLevel{"Log level"};
} // namespace

using namespace Electux::App::View::Settings;
using namespace Electux::App::Model;
using namespace Electux::App::Logger::LogLevels;

LogSettingsTab::LogSettingsTab() : Gtk::Box(Gtk::Orientation::VERTICAL) {
    m_labelLogPath.set_label(cSettingsLogPath.data());
    append(m_labelLogPath);
    append(m_entryLogPath);

    m_labelLogLevel.set_label(cSettingsLogLevel.data());
    append(m_labelLogLevel);
    for (const auto &level : cLogLevels) {
        m_comboLogLevel.append(std::string(level));
    }
    append(m_comboLogLevel);
}

void LogSettingsTab::updateData(const IModel &config) {
    auto pathKey = config.toString(ModelLogKey::FilePath);
    m_entryLogPath.set_text(config.getEntity(pathKey).data());

    auto levelKey = config.toString(ModelLogKey::LogLevel);
    auto levelValue = std::stoi(config.getEntity(levelKey).data());
    m_comboLogLevel.set_active(levelValue);
}

void LogSettingsTab::getData(IModel &config) {
    auto pathKey = config.toString(ModelLogKey::FilePath);
    config.update(pathKey, m_entryLogPath.get_text().raw());

    auto levelKey = config.toString(ModelLogKey::LogLevel);
    config.update(
        levelKey, std::to_string(m_comboLogLevel.get_active_row_number())
    );
}
