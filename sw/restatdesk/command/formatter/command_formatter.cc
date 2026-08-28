////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// command_formatter.cc
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

#include <command/formatter/command_formatter.h>
#include <format>

using namespace Electux::App::Command;

namespace {
    constexpr std::string_view cCmdChOff{"<rs#ch#{}#off#end>"};
    constexpr std::string_view cCmdChToggle{"<rs#ch#{}#{}#end>"};
    constexpr std::string_view cCmdChTmr{"<rs#ch#{}#tmr#{}#end>"};
    constexpr std::string_view cCmdAllOff{"<rs#all#off#end>"};
    constexpr std::string_view cCmdAllOn{"<rs#all#on#end>"};
    constexpr std::string_view cCmdAllMaskPrefix{"<rs#all#mask#"};
    constexpr std::string_view cCmdAllMaskSuffix{"#end>"};
    constexpr std::string_view cCmdChStat{"<rs#ch#{}#stat#end>"};
    constexpr std::string_view cCmdAllStat{"<rs#all#stat#end>"};
    constexpr std::string_view cCmdSysReset{"<rs#sys#reset#end>"};
    constexpr std::string_view cCmdSysId{"<rs#sys#id#end>"};
    constexpr std::string_view cCmdSysVersion{"<rs#sys#version#end>"};
    constexpr std::string_view cOnVal{"on"};
    constexpr std::string_view cOffVal{"off"};
    constexpr std::string_view cBitOne{"1"};
    constexpr std::string_view cBitZero{"0"};
} // namespace

std::string CommandFormatter::getCommandState(
    size_t channelIdx, const Model::Channel::ChannelState &state
) const {
    if (!state.enabled) {
        return std::format(cCmdChOff.data(), channelIdx + 1);
    }

    if (state.mode == Model::Channel::ChannelMode::Toggle) {
        return std::format(
            cCmdChToggle.data(), channelIdx + 1, state.toggle ? cOnVal : cOffVal
        );
    }

    if (state.mode == Model::Channel::ChannelMode::Timer) {
        if (state.timerEnabled) {
            return std::format(cCmdChTmr.data(), channelIdx + 1, state.timer);
        } else {
            return std::format(cCmdChOff.data(), channelIdx + 1);
        }
    }

    return "";
}

std::string CommandFormatter::getCommandPlan(
    const std::vector<Model::Channel::ChannelState> &states
) const {
    std::string cmd = "rs#all#plan";
    bool empty = true;
    for (size_t i = 0; i < states.size(); ++i) {
        const auto &state = states[i];
        if (state.enabled) {
            empty = false;
            cmd += std::format("#ch#{}", i + 1);
            if (state.mode == Model::Channel::ChannelMode::Toggle) {
                cmd += state.toggle ? "#on" : "#off";
            } else if (state.mode == Model::Channel::ChannelMode::Timer) {
                cmd += std::format(
                    "#{}#{}",
                    state.timerEnabled ? "tmron" : "tmroff",
                    state.timer
                );
            } else {
                cmd += "#off";
            }
        }
    }
    if (empty) {
        return "";
    }
    cmd += "#end";
    return std::format("<{}>", cmd);
}

std::string CommandFormatter::getCommandOffAllChannels() const {
    return std::string(cCmdAllOff);
}

std::string CommandFormatter::getCommandOnAllChannels() const {
    return std::string(cCmdAllOn);
}

std::string CommandFormatter::getCommandMaskChannels(
    const std::vector<Model::Channel::ChannelState> &states
) const {
    std::string command = std::string(cCmdAllMaskPrefix);
    for (const auto &state : states) {
        command += (state.enabled and state.toggle ? cBitOne : cBitZero);
    }
    command += cCmdAllMaskSuffix;
    return command;
}

std::string CommandFormatter::getCommandStatus(size_t channelIdx) const {
    return std::format(cCmdChStat.data(), channelIdx + 1);
}

std::string CommandFormatter::getCommandStatusAllChannels() const {
    return std::string(cCmdAllStat);
}

std::string CommandFormatter::getCommandReset() const {
    return std::string(cCmdSysReset);
}

std::string CommandFormatter::getCommandBoardId() const {
    return std::string(cCmdSysId);
}

std::string CommandFormatter::getCommandVersion() const {
    return std::string(cCmdSysVersion);
}
