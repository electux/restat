////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// home.cc
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
#include <view/home.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <gdkmm/display.h>
#include <sstream>
#include <vector>
#include <format>

namespace {
    constexpr std::string_view cHomeTitle{"restatdesk"};
    constexpr int cHomeWidth{600};
    constexpr int cHomeHeight{570};
    constexpr int cWidgetMargin{10};
    constexpr int cScrolledWindowHeight{250};

    std::string formatPlanString(const std::string &data) {
        size_t planPos = data.find("rs#all#plan#");
        if (planPos == std::string::npos) {
            return data;
        }

        std::string prefix = data.substr(0, planPos);
        std::string plan = data.substr(planPos);

        if (prefix == "loading persisted plan: ") {
            prefix = "Loading persisted plan:\n";
        } else if (prefix.empty()) {
            prefix = "Applying plan:\n";
        }

        std::string formatted = prefix;
        
        std::vector<std::string> tokens;
        std::stringstream ss(plan);
        std::string token;
        while (std::getline(ss, token, '#')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }

        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "ch" && i + 2 < tokens.size()) {
                std::string chNum = tokens[i+1];
                std::string mode = tokens[i+2];
                formatted += std::format("  * Channel {}: ", chNum);
                if (mode == "on") {
                    formatted += "ON\n";
                    i += 2;
                } else if (mode == "off") {
                    formatted += "OFF\n";
                    i += 2;
                } else if (mode == "tmron" && i + 3 < tokens.size()) {
                    std::string ms = tokens[i+3];
                    formatted += std::format("Timer ON ({}ms)\n", ms);
                    i += 3;
                } else if (mode == "tmroff" && i + 3 < tokens.size()) {
                    std::string ms = tokens[i+3];
                    formatted += std::format("Timer OFF ({}ms)\n", ms);
                    i += 3;
                } else {
                    formatted += mode + "\n";
                    i += 2;
                }
            }
        }
        if (!formatted.empty() && formatted.back() == '\n') {
            formatted.pop_back();
        }
        return formatted;
    }
} // namespace

using namespace Electux::App::View;
using namespace Electux::App::Model;
using namespace Electux::App::Model::Channel;

AppHome::AppHome() : m_btnExecutePlan("Execute Plan") {
    set_title(cHomeTitle.data());
    set_default_size(cHomeWidth, cHomeHeight);
    set_resizable(false);
    set_show_menubar(true);
    m_boxRoot.set_orientation(Gtk::Orientation::VERTICAL);
    m_boxChannels.set_orientation(Gtk::Orientation::HORIZONTAL);
    m_textView.set_editable(false);
    m_textView.set_cursor_visible(false);
    m_textView.set_wrap_mode(Gtk::WrapMode::CHAR);
    m_textView.set_monospace(true);
    m_textView.set_left_margin(cWidgetMargin);
    m_textView.set_right_margin(cWidgetMargin);
    m_textView.set_top_margin(cWidgetMargin);
    m_textView.set_bottom_margin(cWidgetMargin);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_resource("/electux/restatdesk/style.css");
    Gtk::StyleContext::add_provider_for_display(
        Gdk::Display::get_default(), css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    m_scrolled_window.set_child(m_textView);
    m_scrolled_window.set_vexpand(true);
    m_scrolled_window.set_hexpand(true);
    m_scrolled_window.set_size_request(-1, cScrolledWindowHeight);
    m_scrolled_window.set_margin_start(cWidgetMargin);
    m_scrolled_window.set_margin_end(cWidgetMargin);
    m_scrolled_window.set_margin_bottom(cWidgetMargin);

    m_dispatcher.connect(
        sigc::mem_fun(*this, &AppHome::onDataReceivedDispatcher)
    );

    m_boxActions.set_orientation(Gtk::Orientation::HORIZONTAL);
    m_boxActions.set_margin(cWidgetMargin);
    m_btnExecutePlan.set_halign(Gtk::Align::CENTER);
    m_btnExecutePlan.set_hexpand(true);
    m_boxActions.append(m_btnExecutePlan);

    m_btnExecutePlan.signal_clicked().connect([this]() {
        m_signalExecutePlan.emit();
    });

    m_boxRoot.append(m_boxChannels);
    m_boxRoot.append(m_boxActions);
    m_boxRoot.append(m_scrolled_window);
    set_child(m_boxRoot);

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        auto widget = std::make_unique<ChannelWidget>(static_cast<size_t>(i));

        widget->signal_changed().connect(
            sigc::bind(
                sigc::mem_fun(*this, &AppHome::onChannelChanged),
                static_cast<size_t>(i)
            )
        );

        m_boxChannels.append(*widget);
        m_channelWidgets.push_back(std::move(widget));
    }
}

SigSettings AppHome::controlChanged() { return m_controlSignal; }

void AppHome::setControlSetup(const SettingsSetup &setup) { m_setup = setup; }

void AppHome::updateUiData() {
    const auto &config = *m_setup.m_config;

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        m_channelWidgets[static_cast<size_t>(i)]->updateState(
            config.getChannelState(static_cast<size_t>(i))
        );
    }
}

void AppHome::getUiData() {
    auto &config = *m_setup.m_config;

    for (ssize_t i = 0; i < cNumOfChannels; i++) {
        config.setChannelState(
            static_cast<size_t>(i),
            m_channelWidgets[static_cast<size_t>(i)]->getState()
        );
    }

    m_controlSignal.emit(m_setup);
}

void AppHome::onChannelChanged(size_t index) {
    auto &config = *m_setup.m_config;
    config.setChannelState(index, m_channelWidgets[index]->getState());
    m_controlSignal.emit(m_setup);
}

void AppHome::show() { set_visible(true); }

void AppHome::hide() { set_visible(false); }

void AppHome::connect_close_request(const sigc::slot<bool()> &slot) {
    signal_close_request().connect(slot, false);
}

Gtk::Window &AppHome::getGtkWindow() { return *this; }

void AppHome::postData(const std::string &data) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_incomingDataQueue.push(data);
    m_dispatcher.emit();
}

void AppHome::onDataReceivedDispatcher() {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto buffer = m_textView.get_buffer();

    while (!m_incomingDataQueue.empty()) {
        std::string data = m_incomingDataQueue.front();
        
        updateLedsFromMessage(data);

        buffer->insert(buffer->end(), formatPlanString(data));
        buffer->insert(buffer->end(), "\n");

        m_incomingDataQueue.pop();
    }
}

void AppHome::updateLedsFromMessage(const std::string &msg) {
    // 0. Check for "rs#all#plan#"
    size_t planPos = msg.find("rs#all#plan#");
    if (planPos != std::string::npos) {
        std::string plan = msg.substr(planPos);
        std::vector<std::string> tokens;
        std::stringstream ss(plan);
        std::string token;
        while (std::getline(ss, token, '#')) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "ch" && i + 2 < tokens.size()) {
                int chNum = std::stoi(tokens[i+1]);
                std::string mode = tokens[i+2];
                if (chNum >= 1 && chNum <= 8) {
                    bool is_on = false;
                    if (mode == "on" || mode == "tmron") {
                        is_on = true;
                    } else if (mode == "off" || mode == "tmroff") {
                        is_on = false;
                    }
                    m_channelWidgets[static_cast<size_t>(chNum - 1)]->setLedState(is_on);
                }
                i += 2;
                if (mode == "tmron" || mode == "tmroff") {
                    i++; // skip duration
                }
            }
        }
        return;
    }

    // 0.5. Check for "all channels on" or "all channels off"
    if (msg.find("all channels on") != std::string::npos) {
        for (size_t i = 0; i < 8; ++i) {
            m_channelWidgets[i]->setLedState(true);
        }
        return;
    }
    if (msg.find("all channels off") != std::string::npos) {
        for (size_t i = 0; i < 8; ++i) {
            m_channelWidgets[i]->setLedState(false);
        }
        return;
    }

    // 0.6. Check for "channels mask applied: 10101010"
    size_t maskPos = msg.find("channels mask applied: ");
    if (maskPos != std::string::npos) {
        std::string mask = msg.substr(maskPos + 23, 8);
        for (size_t i = 0; i < 8 && i < mask.length(); ++i) {
            m_channelWidgets[i]->setLedState(mask[i] == '1');
        }
        return;
    }

    // 1. Check for "channels: 1:OFF 2:ON ..."
    size_t channelsPos = msg.find("channels: ");
    if (channelsPos != std::string::npos) {
        std::string listStr = msg.substr(channelsPos + 10);
        std::stringstream ss(listStr);
        std::string item;
        while (ss >> item) {
            size_t colon = item.find(':');
            if (colon != std::string::npos) {
                int chNum = std::stoi(item.substr(0, colon));
                std::string state = item.substr(colon + 1);
                if (chNum >= 1 && chNum <= 8) {
                    m_channelWidgets[static_cast<size_t>(chNum - 1)]->setLedState(state == "ON");
                }
            }
        }
        return;
    }

    // 2. Check for "channel X on" or "channel X off"
    size_t channelPos = msg.find("channel ");
    if (channelPos != std::string::npos) {
        std::string sub = msg.substr(channelPos + 8);
        std::stringstream ss(sub);
        int chNum = 0;
        std::string state;
        if (ss >> chNum >> state) {
            if (chNum >= 1 && chNum <= 8) {
                m_channelWidgets[static_cast<size_t>(chNum - 1)]->setLedState(state == "on");
            }
        }
        return;
    }

    // 3. Check for "Channel X: ON" or "Channel X: OFF"
    size_t channelCapPos = msg.find("Channel ");
    if (channelCapPos != std::string::npos) {
        std::string sub = msg.substr(channelCapPos + 8);
        std::stringstream ss(sub);
        int chNum = 0;
        std::string colon;
        std::string state;
        if (ss >> chNum >> colon >> state) {
            if (colon == ":" && chNum >= 1 && chNum <= 8) {
                m_channelWidgets[static_cast<size_t>(chNum - 1)]->setLedState(state == "ON");
            }
        }
        return;
    }
}
