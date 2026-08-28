////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// icommand_formatter.h
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
#pragma once

#include <model/channel_state.h>
#include <string>
#include <vector>

namespace Electux::App::Command {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ICommandFormatter
    /// @brief Interface defining the contract for parsing relay channel state
    /// into protocol strings.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ICommandFormatter {
      public:
        virtual ~ICommandFormatter() = default;

        virtual std::string getCommandState(
            size_t channelIdx, const Model::Channel::ChannelState &state
        ) const = 0;
        virtual std::string getCommandPlan(
            const std::vector<Model::Channel::ChannelState> &states
        ) const = 0;
        virtual std::string getCommandOffAllChannels() const = 0;
        virtual std::string getCommandOnAllChannels() const = 0;
        virtual std::string getCommandMaskChannels(
            const std::vector<Model::Channel::ChannelState> &states
        ) const = 0;
        virtual std::string getCommandStatus(size_t channelIdx) const = 0;
        virtual std::string getCommandStatusAllChannels() const = 0;
        virtual std::string getCommandReset() const = 0;
        virtual std::string getCommandBoardId() const = 0;
        virtual std::string getCommandVersion() const = 0;
    };
} // namespace Electux::App::Command
