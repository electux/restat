////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// control_model_delegate.cc
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

#include <model/delegate/control/control_model_delegate.h>
#include <model/channel_types.h>
#include <algorithm>
#include <initializer_list>
#include <sstream>
#include <vector>

namespace Electux::App::Model {
    namespace {
        constexpr std::string_view cEnable{"enable"};
        constexpr std::string_view cMode{"mode"};
        constexpr std::string_view cToggle{"toggle"};
        constexpr std::string_view cTimer{"timer"};
        constexpr std::string_view cTimerEnable{"timerEnable"};
        constexpr std::string_view cUnknown{"unknown"};
        constexpr std::string_view cTrueVal{"true"};
        constexpr std::string_view cFalseVal{"false"};
        constexpr std::string_view cModeToggleVal{"0"};
        constexpr std::string_view cModeTimerVal{"1"};
        constexpr std::string_view cModeToggle{"toggle"};
        constexpr std::string_view cModeTimer{"timer"};

        std::vector<std::string> split_to_vector(const std::string_view &input) {
            std::vector<std::string> elements;
            std::stringstream ss{std::string(input)};
            std::string item;
            while (ss >> item) {
                elements.push_back(item);
            }
            return elements;
        }

        std::string extract_param_value_by_index(
            const std::string_view &input, size_t index
        ) {
            auto elements = split_to_vector(input);
            if (index < elements.size()) {
                return elements[index];
            }
            return "";
        }

        std::string update_param_value_by_index(
            const std::string_view &input, size_t index,
            const std::string_view &newValue
        ) {
            auto elements = split_to_vector(input);
            if (elements.size() < static_cast<size_t>(Electux::App::Model::Channel::cNumOfChannels)) {
                std::string defaultValue =
                    elements.empty() ? std::string(newValue) : elements.back();
                elements.resize(
                    static_cast<size_t>(Electux::App::Model::Channel::cNumOfChannels),
                    defaultValue
                );
            }
            if (index < elements.size()) {
                elements[index] = std::string(newValue);
            }
            std::string result;
            for (size_t i = 0; i < elements.size(); ++i) {
                result += elements[i] + (i < elements.size() - 1 ? " " : "");
            }
            return result;
        }
    } // namespace

    std::string_view ControlModelDelegate::toString(ModelControlKey key) const {
        switch (key) {
        case ModelControlKey::Enable:
            return cEnable;
        case ModelControlKey::Mode:
            return cMode;
        case ModelControlKey::Toggle:
            return cToggle;
        case ModelControlKey::Timer:
            return cTimer;
        case ModelControlKey::TimerEnable:
            return cTimerEnable;
        default:
            return cUnknown;
        }
    }

    bool ControlModelDelegate::validateKey(const std::string_view &key) const {
        static const std::initializer_list<std::string_view> validKeys = {
            cEnable, cMode, cToggle, cTimer, cTimerEnable
        };
        return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) {
            return k == key;
        });
    }

    ChannelState ControlModelDelegate::getChannelState(const Entities &entities, size_t index) const {
        using Electux::App::Model::Channel::ChannelMode;

        auto getEntityStr = [&](ModelControlKey key) -> std::string {
            auto keyStr = std::string(toString(key));
            auto it = entities.find(keyStr);
            if (it != entities.end()) {
                return it->second;
            }
            return "";
        };

        ChannelState state;

        state.enabled = (extract_param_value_by_index(getEntityStr(ModelControlKey::Enable), index) == cTrueVal);

        auto modeStr = extract_param_value_by_index(getEntityStr(ModelControlKey::Mode), index);
        if (modeStr.empty()) {
            state.mode = ChannelMode::Unknown;
        } else if (modeStr == cModeToggleVal || modeStr == cModeToggle) {
            state.mode = ChannelMode::Toggle;
        } else if (modeStr == cModeTimerVal || modeStr == cModeTimer) {
            state.mode = ChannelMode::Timer;
        } else {
            state.mode = ChannelMode::Unknown;
        }

        state.toggle = (extract_param_value_by_index(getEntityStr(ModelControlKey::Toggle), index) == cTrueVal);

        auto timerStr = extract_param_value_by_index(getEntityStr(ModelControlKey::Timer), index);
        state.timer = timerStr.empty() ? 0 : std::stoi(timerStr);

        state.timerEnabled = (extract_param_value_by_index(getEntityStr(ModelControlKey::TimerEnable), index) == cTrueVal);

        return state;
    }

    void ControlModelDelegate::setChannelState(
        Entities &entities, size_t index, const ChannelState &state
    ) const {
        using Electux::App::Model::Channel::toConfigString;

        auto updateEntity = [&](ModelControlKey key, const std::string &newValue) {
            auto keyStr = std::string(toString(key));
            auto it = entities.find(keyStr);
            if (it != entities.end()) {
                it->second = update_param_value_by_index(it->second, index, newValue);
            }
        };

        updateEntity(ModelControlKey::Enable, state.enabled ? std::string(cTrueVal) : std::string(cFalseVal));
        updateEntity(ModelControlKey::Mode, std::string(toConfigString(state.mode)));
        updateEntity(ModelControlKey::Toggle, state.toggle ? std::string(cTrueVal) : std::string(cFalseVal));
        updateEntity(ModelControlKey::Timer, std::to_string(state.timer));
        updateEntity(ModelControlKey::TimerEnable, state.timerEnabled ? std::string(cTrueVal) : std::string(cFalseVal));
    }

    std::unique_ptr<IControlModelDelegate> ControlModelDelegate::clone() const {
        return std::make_unique<ControlModelDelegate>(*this);
    }
} // namespace Electux::App::Model
