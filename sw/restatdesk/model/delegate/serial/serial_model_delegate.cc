////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_model_delegate.cc
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

#include <model/delegate/serial/serial_model_delegate.h>
#include <algorithm>
#include <initializer_list>

namespace Electux::App::Model {
    namespace {
        constexpr std::string_view cDevice{"device"};
        constexpr std::string_view cBaud{"baud"};
        constexpr std::string_view cData{"data"};
        constexpr std::string_view cParity{"parity"};
        constexpr std::string_view cStop{"stop"};
        constexpr std::string_view cFlow{"flow"};
        constexpr std::string_view cUnknown{"unknown"};
    } // namespace

    std::string_view SerialModelDelegate::toString(ModelSerialKey key) const {
        switch (key) {
        case ModelSerialKey::Device:
            return cDevice;
        case ModelSerialKey::Baud:
            return cBaud;
        case ModelSerialKey::Data:
            return cData;
        case ModelSerialKey::Parity:
            return cParity;
        case ModelSerialKey::Stop:
            return cStop;
        case ModelSerialKey::Flow:
            return cFlow;
        default:
            return cUnknown;
        }
    }

    bool SerialModelDelegate::validateKey(const std::string_view &key) const {
        static const std::initializer_list<std::string_view> validKeys = {
            cDevice, cBaud, cData, cParity, cStop, cFlow
        };
        return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) {
            return k == key;
        });
    }

    std::unique_ptr<ISerialModelDelegate> SerialModelDelegate::clone() const {
        return std::make_unique<SerialModelDelegate>(*this);
    }
} // namespace Electux::App::Model
