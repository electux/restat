////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// icontrol_model_delegate.h
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
#include <memory>
#include <string_view>

namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IControlModelDelegate
    /// @brief Interface for control and channel settings delegates.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IControlModelDelegate {
      public:
        virtual ~IControlModelDelegate() = default;

        virtual std::string_view toString(ModelControlKey key) const = 0;
        virtual bool validateKey(const std::string_view &key) const = 0;

        virtual ChannelState getChannelState(const Entities &entities, size_t index) const = 0;
        virtual void setChannelState(Entities &entities, size_t index, const ChannelState &state) const = 0;

        virtual std::unique_ptr<IControlModelDelegate> clone() const = 0;
    };
} // namespace Electux::App::Model
