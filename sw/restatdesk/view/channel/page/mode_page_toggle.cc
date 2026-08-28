////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// mode_page_toggle.cc
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
#include <format>
#include <view/channel/page/mode_page_toggle.h>

namespace {
    constexpr std::string_view cChannelToggleBtnActivate{"Activate"};
    constexpr std::string_view cChannelToggleDesc{"Manually control the channel state."};
    constexpr int cBoxSpacing{5};
    constexpr int cMarginTopBottom{15};
} // namespace

using namespace Electux::App::View;

ToggleModePage::ToggleModePage(size_t index)
    : Gtk::Box(Gtk::Orientation::VERTICAL, cBoxSpacing),
      m_index(index) {
    m_descLabel.set_label(cChannelToggleDesc.data());

    m_descLabel.set_wrap(true);
    m_descLabel.set_justify(Gtk::Justification::CENTER);
    m_descLabel.set_margin_top(cMarginTopBottom);
    m_descLabel.set_margin_bottom(cMarginTopBottom);
    m_descLabel.set_vexpand(true);
    m_descLabel.set_valign(Gtk::Align::END);
    append(m_descLabel);

    m_toggleBtn.set_label(cChannelToggleBtnActivate.data());
    append(m_toggleBtn);

    m_progressBar.set_fraction(0.0);
    append(m_progressBar);

    m_toggleBtn.signal_clicked().connect(
        sigc::mem_fun(*this, &ToggleModePage::onToggleClicked)
    );
}

void ToggleModePage::updateState(const ChannelState &state) {
    m_toggleBtn.set_active(state.toggle);
    m_toggleBtn.set_label(state.toggle ? "Deactive" : "Activate");
    m_progressBar.set_fraction(state.toggle ? 1.0 : 0.0);
}

void ToggleModePage::getState(ChannelState &state) const {
    state.toggle = m_toggleBtn.get_active();
}

void ToggleModePage::onToggleClicked() {
    bool active = m_toggleBtn.get_active();
    m_toggleBtn.set_label(active ? "Deactive" : "Activate");
    m_progressBar.set_fraction(active ? 1.0 : 0.0);
    m_signalChanged.emit();
}
