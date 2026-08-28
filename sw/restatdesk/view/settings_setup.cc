////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings_setup.cc
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
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <model/imodel.h>
#include <view/settings_setup.h>

namespace Electux::App::Model {
    SettingsSetup::SettingsSetup() : m_config(nullptr) {}

    SettingsSetup::~SettingsSetup() = default;

    SettingsSetup::SettingsSetup(const SettingsSetup &other)
        : m_config(other.m_config ? other.m_config->clone() : nullptr) {}

    SettingsSetup &SettingsSetup::operator=(const SettingsSetup &other) {
        if (this != &other) {
            m_config = other.m_config ? other.m_config->clone() : nullptr;
        }
        return *this;
    }

    SettingsSetup::SettingsSetup(SettingsSetup &&) noexcept = default;
    SettingsSetup &
    SettingsSetup::operator=(SettingsSetup &&) noexcept = default;
} // namespace Electux::App::Model
