////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ble_com_configurator.h
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

#include <com/icom_configurator.h>

namespace Electux::App::Com {
    class IBle;
    class ICom;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BleComConfigurator
    /// @brief Configures BLE communication parameters using the model.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BleComConfigurator : public IComConfigurator {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs a new BleComConfigurator object.
        /// @param ble Pointer to the IBle interface representing the BLE channel.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        explicit BleComConfigurator(IBle *ble);

        ~BleComConfigurator() override = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the BLE connection.
        /// @param model Reference to the configuration model.
        /// @param comChannel Pointer to the communication channel interface.
        /// @return true if configuration was successful, else false.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool configure(const Model::IModel &model, ICom *comChannel) override;

      private:
        IBle *m_ble;
    };
} // namespace Electux::App::Com
