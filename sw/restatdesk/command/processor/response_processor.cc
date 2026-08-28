////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// response_processor.cc
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

#include <command/processor/response_processor.h>

using namespace Electux::App::Command;

namespace {
    constexpr std::string_view cStartMarker{"<rs#sys#"};
    constexpr std::string_view cEndMarker{"#end>"};
} // namespace

std::vector<std::string> ResponseProcessor::process(const std::string &data) {
    m_buffer += data;
    std::vector<std::string> payloads;

    while (true) {
        size_t startPos = m_buffer.find(cStartMarker);

        if (startPos == std::string::npos) {
            size_t lastLessThan = m_buffer.rfind('<');

            if (lastLessThan != std::string::npos) {
                m_buffer = m_buffer.substr(lastLessThan);
            } else {
                m_buffer.clear();
            }

            break;
        }

        size_t endPos = m_buffer.find(cEndMarker, startPos);

        if (endPos == std::string::npos) {
            if (startPos > 0) {
                m_buffer = m_buffer.substr(startPos);
            }

            break;
        }

        size_t payloadStart = startPos + cStartMarker.length();
        size_t payloadLen = endPos - payloadStart;

        std::string payload = m_buffer.substr(payloadStart, payloadLen);
        payloads.push_back(payload);

        m_buffer = m_buffer.substr(endPos + cEndMarker.length());
    }

    return payloads;
}
