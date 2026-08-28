////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// model_factory.cc
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

#include <model/model_factory.h>
#include <model/model.h>
#include <model/delegate/control/control_model_delegate.h>
#include <model/delegate/serial/serial_model_delegate.h>
#include <model/delegate/general/general_model_delegate.h>
#include <model/delegate/ble/ble_model_delegate.h>
#include <model/delegate/log/log_model_delegate.h>

namespace Electux::App::Model {
    std::unique_ptr<IModel> createDefault() {
        return std::make_unique<Model>(
            std::make_unique<ControlModelDelegate>(),
            std::make_unique<SerialModelDelegate>(),
            std::make_unique<GeneralModelDelegate>(),
            std::make_unique<BleModelDelegate>(),
            std::make_unique<LogModelDelegate>()
        );
    }
} // namespace Electux::App::Model
