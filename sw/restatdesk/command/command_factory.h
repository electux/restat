////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// command_factory.h
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

#include <command/formatter/icommand_formatter.h>
#include <command/processor/iresponse_processor.h>
#include <memory>

namespace Electux::App::Command {
    std::unique_ptr<ICommandFormatter> createCommandFormatter();
    std::unique_ptr<IResponseProcessor> createResponseProcessor();
} // namespace Electux::App::Command
