////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// command_factory.cc
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

#include <command/command_factory.h>
#include <command/formatter/command_formatter.h>
#include <command/processor/response_processor.h>

namespace Electux::App::Command {
    std::unique_ptr<ICommandFormatter> createCommandFormatter() {
        return std::make_unique<CommandFormatter>();
    }

    std::unique_ptr<IResponseProcessor> createResponseProcessor() {
        return std::make_unique<ResponseProcessor>();
    }
} // namespace Electux::App::Command
