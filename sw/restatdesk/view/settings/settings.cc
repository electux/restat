////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// settings.cc
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

#include <model/model.h>
#include <view/settings/settings.h>

namespace {
    constexpr std::string_view cSettingsTitle{"restatdesk"};
    constexpr int cSettingsWidth{320};
    constexpr int cSettingsHeight{320};
    constexpr int cSettingsNotebookMargin{10};
    constexpr std::string_view cSettingsPageGeneralLabel{"General"};
    constexpr std::string_view cSettingsPageSerialLabel{"Serial port"};
    constexpr std::string_view cSettingsPageTcpLabel{"TCP/IP"};
    constexpr std::string_view cSettingsPageBleLabel{"BLE"};
    constexpr std::string_view cSettingsPageLogLabel{"Log"};

    constexpr int cSettingsButtonBoxWidth{220};
    constexpr int cSettingsButtonBoxHeight{60};
    constexpr int cSettingsButtonBoxMargin{10};
    constexpr int cSettingsButtonBoxRowSpacing{5};
    constexpr int cSettingsButtonBoxColumnSpacing{5};
    constexpr std::string_view cSettingsButtonOkLabel{"Ok"};
    constexpr std::string_view cSettingsButtonCancelLabel{"Cancel"};
    constexpr int cSettingsButtonWidth{100};
    constexpr int cSettingsButtonHeight{50};
    constexpr int cSettingsGridRowColumnOccupyZero{0};
    constexpr int cSettingsGridRowColumnOccupyOne{1};
} // namespace

using namespace Electux::App::View::Settings;

AppSettings::AppSettings() {
    set_title(cSettingsTitle.data());
    set_default_size(cSettingsWidth, cSettingsHeight);
    set_resizable(false);
    set_hide_on_close(true);
    set_child(m_boxRoot);

    m_boxRoot.set_orientation(Gtk::Orientation::VERTICAL);
    m_notebook.set_margin(cSettingsNotebookMargin);
    m_notebook.set_expand();

    m_notebook.append_page(m_generalTab, cSettingsPageGeneralLabel.data());
    m_notebook.append_page(m_serialTab, cSettingsPageSerialLabel.data());
    m_notebook.append_page(m_tcpTab, cSettingsPageTcpLabel.data());
    m_notebook.append_page(m_bleTab, cSettingsPageBleLabel.data());
    m_notebook.append_page(m_logTab, cSettingsPageLogLabel.data());
    m_boxRoot.append(m_notebook);

    m_buttonBox.set_size_request(
        cSettingsButtonBoxWidth, cSettingsButtonBoxHeight
    );
    m_buttonBox.set_margin(cSettingsButtonBoxMargin);

    m_buttonOk.set_label(cSettingsButtonOkLabel.data());
    m_buttonOk.set_size_request(cSettingsButtonWidth, cSettingsButtonHeight);

    m_buttonCancel.set_label(cSettingsButtonCancelLabel.data());
    m_buttonCancel.set_size_request(
        cSettingsButtonWidth, cSettingsButtonHeight
    );

    m_buttonBox.attach(
        m_buttonCancel, cSettingsGridRowColumnOccupyZero,
        cSettingsGridRowColumnOccupyZero
    );
    m_buttonBox.attach(
        m_buttonOk, cSettingsGridRowColumnOccupyOne,
        cSettingsGridRowColumnOccupyZero
    );

    m_buttonBox.set_hexpand(false);
    m_buttonBox.set_vexpand(false);
    m_buttonBox.set_row_spacing(cSettingsButtonBoxRowSpacing);
    m_buttonBox.set_column_spacing(cSettingsButtonBoxColumnSpacing);

    m_boxRoot.append(m_buttonBox);

    mapping();
}

SigSetup AppSettings::setupChanged() { return m_setupSignal; }

void AppSettings::setSettingsSetup(const SettingsSetup &setup) {
    m_setup = setup;
}

void AppSettings::updateUiData() {
    m_generalTab.updateData(*m_setup.m_config);
    m_serialTab.updateData(*m_setup.m_config);
    m_tcpTab.updateData(*m_setup.m_config);
    m_bleTab.updateData(*m_setup.m_config);
    m_logTab.updateData(*m_setup.m_config);
}

void AppSettings::getUiData() {
    m_generalTab.getData(*m_setup.m_config);
    m_serialTab.getData(*m_setup.m_config);
    m_tcpTab.getData(*m_setup.m_config);
    m_bleTab.getData(*m_setup.m_config);
    m_logTab.getData(*m_setup.m_config);
}

void AppSettings::mapping() {
    m_buttonOk.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::onButtonOkClicked)
    );

    m_buttonCancel.signal_clicked().connect(
        sigc::mem_fun(*this, &AppSettings::onButtonCancelClicked)
    );
}

void AppSettings::onButtonOkClicked() {
    getUiData();
    m_setupSignal.emit(m_setup);
    hide();
}

void AppSettings::onButtonCancelClicked() { hide(); }

void AppSettings::show() { set_visible(true); }

void AppSettings::hide() { set_visible(false); }
