////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// iresponse_processor.h
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

#include <string>
#include <vector>

namespace Electux::App::Command {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IResponseProcessor
    /// @brief Interface defining the contract for parsing raw incoming data streams into response payloads.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IResponseProcessor {
      public:
        virtual ~IResponseProcessor() = default;

        /// @brief Processes incoming raw data, buffering as needed, and extracts complete response payloads.
        /// @param data String containing a chunk of raw incoming data.
        /// @return Vector of extracted payload strings.
        virtual std::vector<std::string> process(const std::string &data) = 0;
    };
} // namespace Electux::App::Command
