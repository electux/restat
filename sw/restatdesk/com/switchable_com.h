////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// switchable_com.h
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

#include <com/icom.h>
#include <memory>
#include <string>

namespace Electux::App::Com {
    class SerialCom;
    class TcpCom;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class SwitchableCom
    /// @brief Proxy/Decorator implementing ICom that switches between Serial
    /// and TCP at runtime.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class SwitchableCom : public ICom {
      public:
        SwitchableCom(
            bool verbose,
            std::unique_ptr<ICom> serialCom,
            std::unique_ptr<ICom> tcpCom,
            std::unique_ptr<ICom> bleCom
        );
        ~SwitchableCom() override = default;

        SwitchableCom(const SwitchableCom &) = delete;
        SwitchableCom &operator=(const SwitchableCom &) = delete;

        // ICom overrides
        bool open() override;
        bool close() override;
        bool isOpen() const override;
        void read(std::vector<uint8_t> &data, size_t len) override;
        void write(const std::vector<uint8_t> &data) override;

        // Active channel control
        void setComType(const std::string &type);
        ICom *getActiveCom() const;

        ICom *getSerialCom() const;
        ICom *getTcpCom() const;
        ICom *getBleCom() const;

      private:
        bool m_verbose;
        std::unique_ptr<ICom> m_serialCom;
        std::unique_ptr<ICom> m_tcpCom;
        std::unique_ptr<ICom> m_bleCom;
        ICom *m_activeCom;
    };
} // namespace Electux::App::Com
