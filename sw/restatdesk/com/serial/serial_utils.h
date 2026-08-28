////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_utils.h
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

#include <com/serial/serialw/ilib.h>
#include <cstdint>

namespace Electux::App::Com::SerialUtils {
    uint32_t baudToUint(const BaudRate baud);
    BaudRate uintToBaud(const uint32_t baud);

    uint32_t dataBitsToUint(const CharacterSize data);
    CharacterSize uintToDataBits(const uint32_t data);

    uint32_t parityToUint(const Parity parity);
    Parity uintToParity(const uint32_t parity);

    uint32_t stopBitsToUint(const StopBits stop);
    StopBits uintToStopBits(const uint32_t stop);

    uint32_t flowControlToUint(const FlowControl flow);
    FlowControl uintToFlowControl(const uint32_t flow);
} // namespace Electux::App::Com::SerialUtils
