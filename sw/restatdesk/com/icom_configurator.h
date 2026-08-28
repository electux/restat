////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// icom_configurator.h
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

namespace Electux::App::Model {
    class IModel;
}

namespace Electux::App::Com {
    class ICom;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IComConfigurator
    /// @brief Interface for protocol-independent configuration of communication
    /// channels.
    ///
    /// This class abstracts the parameters configuration for any communication
    /// mechanism (Serial, TCP, etc.) from the AppController.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IComConfigurator {
      public:
        virtual ~IComConfigurator() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the communication channel using parameters from
        /// the model.
        /// @param model Reference to the configuration model.
        /// @param comChannel Pointer to the communication channel interface.
        /// @return true if configuration was successful, else false.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool
        configure(const Model::IModel &model, ICom *comChannel) = 0;
    };
} // namespace Electux::App::Com
