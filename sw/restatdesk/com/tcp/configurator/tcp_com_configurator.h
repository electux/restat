////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// tcp_com_configurator.h
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
    class ITcp;
    class ICom;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class TcpComConfigurator
    /// @brief Configures TCP/IP communication parameters using the model.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class TcpComConfigurator : public IComConfigurator {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs a new TcpComConfigurator object.
        /// @param tcp Pointer to the ITcp interface representing the TCP
        /// channel.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        explicit TcpComConfigurator(ITcp *tcp);

        ~TcpComConfigurator() override = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Configures the TCP/IP connection.
        /// @param model Reference to the configuration model.
        /// @param comChannel Pointer to the communication channel interface.
        /// @return true if configuration was successful, else false.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool configure(const Model::IModel &model, ICom *comChannel) override;

      private:
        ITcp *m_tcp;
    };
} // namespace Electux::App::Com
