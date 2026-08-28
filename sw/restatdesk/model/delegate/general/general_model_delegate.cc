////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// general_model_delegate.cc
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

#include <model/delegate/general/general_model_delegate.h>
#include <algorithm>
#include <initializer_list>

namespace Electux::App::Model {
    namespace {
        constexpr std::string_view cComType{"com_type"};
        constexpr std::string_view cTcpIp{"tcp_ip"};
        constexpr std::string_view cTcpPort{"tcp_port"};
        constexpr std::string_view cUnknown{"unknown"};
    } // namespace

    std::string_view GeneralModelDelegate::toString(ModelGeneralKey key) const {
        switch (key) {
        case ModelGeneralKey::ComType:
            return cComType;
        case ModelGeneralKey::TcpIp:
            return cTcpIp;
        case ModelGeneralKey::TcpPort:
            return cTcpPort;
        default:
            return cUnknown;
        }
    }

    bool GeneralModelDelegate::validateKey(const std::string_view &key) const {
        static const std::initializer_list<std::string_view> validKeys = {
            cComType, cTcpIp, cTcpPort
        };
        return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) {
            return k == key;
        });
    }

    std::unique_ptr<IGeneralModelDelegate> GeneralModelDelegate::clone() const {
        return std::make_unique<GeneralModelDelegate>(*this);
    }
} // namespace Electux::App::Model
