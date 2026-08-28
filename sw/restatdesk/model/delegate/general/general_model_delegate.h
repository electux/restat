////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// general_model_delegate.h
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

#include <model/imodel.h>
#include <model/delegate/general/igeneral_model_delegate.h>
#include <memory>
#include <string_view>

namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class GeneralModelDelegate
    /// @brief Handles general communication configuration keys and validation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class GeneralModelDelegate : public IGeneralModelDelegate {
      public:
        GeneralModelDelegate() = default;
        ~GeneralModelDelegate() override = default;

        std::string_view toString(ModelGeneralKey key) const override;
        bool validateKey(const std::string_view &key) const override;

        std::unique_ptr<IGeneralModelDelegate> clone() const override;
    };
} // namespace Electux::App::Model
