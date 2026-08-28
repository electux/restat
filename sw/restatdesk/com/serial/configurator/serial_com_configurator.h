////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com_configurator.h
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
    class ISerial;
    class ICom;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class SerialComConfigurator
    /// @brief Configures serial communication parameters using the model.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class SerialComConfigurator : public IComConfigurator {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs a new SerialComConfigurator object.
        /// @param serial Pointer to the ISerial interface representing the
        /// serial channel.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        explicit SerialComConfigurator(ISerial *serial);

        ~SerialComConfigurator() override = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the serial port.
        /// @param model Reference to the configuration model.
        /// @param comChannel Pointer to the communication channel interface.
        /// @return true if configuration was successful, else false.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool configure(const Model::IModel &model, ICom *comChannel) override;

      private:
        ISerial *m_serial;
    };
} // namespace Electux::App::Com
