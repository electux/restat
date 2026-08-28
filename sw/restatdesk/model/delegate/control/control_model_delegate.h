////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// control_model_delegate.h
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
#include <model/delegate/control/icontrol_model_delegate.h>
#include <memory>
#include <string_view>

namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class ControlModelDelegate
    /// @brief Handles control and channel configuration keys, validation, and states.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class ControlModelDelegate : public IControlModelDelegate {
      public:
        ControlModelDelegate() = default;
        ~ControlModelDelegate() override = default;

        std::string_view toString(ModelControlKey key) const override;
        bool validateKey(const std::string_view &key) const override;

        ChannelState getChannelState(const Entities &entities, size_t index) const override;
        void setChannelState(Entities &entities, size_t index, const ChannelState &state) const override;

        std::unique_ptr<IControlModelDelegate> clone() const override;
    };
} // namespace Electux::App::Model
