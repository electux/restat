////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// log_model_delegate.cc
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

#include <model/delegate/log/log_model_delegate.h>
#include <algorithm>
#include <initializer_list>

namespace Electux::App::Model {
    namespace {
        constexpr std::string_view cLogLevel{"log_level"};
        constexpr std::string_view cFilePath{"log_file_path"};
        constexpr std::string_view cUnknown{"unknown"};
    } // namespace

    std::string_view LogModelDelegate::toString(ModelLogKey key) const {
        switch (key) {
        case ModelLogKey::LogLevel:
            return cLogLevel;
        case ModelLogKey::FilePath:
            return cFilePath;
        default:
            return cUnknown;
        }
    }

    bool LogModelDelegate::validateKey(const std::string_view &key) const {
        static const std::initializer_list<std::string_view> validKeys = {
            cLogLevel, cFilePath
        };
        return std::any_of(validKeys.begin(), validKeys.end(), [&](auto k) {
            return k == key;
        });
    }

    std::unique_ptr<ILogModelDelegate> LogModelDelegate::clone() const {
        return std::make_unique<LogModelDelegate>(*this);
    }
} // namespace Electux::App::Model
