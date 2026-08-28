////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_manager_utils.cc
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
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <config/config_manager.h>
#include <model/model.h>

namespace {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Internal Configuration Constants
    /// @{
    // Default values for Control Model
    constexpr std::string_view cConfigDefaultControlEnable{
        "false false false false false false false false"
    };
    constexpr std::string_view cConfigDefaultControlMode{
        "0 0 0 0 0 0 0 0"
    };
    constexpr std::string_view cConfigDefaultControlToggle{
        "false false false false false false false false"
    };
    constexpr std::string_view cConfigDefaultControlTimer{"0 0 0 0 0 0 0 0"};
    constexpr std::string_view cConfigDefaultControlTimerEnable{
        "false false false false false false false false"
    };
    // Default values for Serial Model
    constexpr std::string_view cConfigDefaultSerialDevice{"/dev/ttyUSB0"};
    constexpr std::string_view cConfigDefaultSerialBaud{"10"};
    constexpr std::string_view cConfigDefaultSerialData{"3"};
    constexpr std::string_view cConfigDefaultSerialParity{"2"};
    constexpr std::string_view cConfigDefaultSerialStop{"0"};
    constexpr std::string_view cConfigDefaultSerialFlow{"0"};
    // Default values for Log Model
    constexpr std::string_view cConfigDefaultLogFilePath{"/tmp/restatdesk.log"
    };
    constexpr std::string_view cConfigDefaultLogLevel{"2"};
    // Default values for General Model
    constexpr std::string_view cConfigDefaultGeneralComType{"serial"};
    constexpr std::string_view cConfigDefaultGeneralTcpIp{"127.0.0.1"};
    constexpr std::string_view cConfigDefaultGeneralTcpPort{"5000"};
    // Default values for BLE Model
    constexpr std::string_view cConfigDefaultBleAddress{"00:00:00:00:00:00"};
    constexpr std::string_view cConfigDefaultBleServiceUuid{"0000ffe0-0000-1000-8000-00805f9b34fb"};
    constexpr std::string_view cConfigDefaultBleRxUuid{"0000ffe1-0000-1000-8000-00805f9b34fb"};
    constexpr std::string_view cConfigDefaultBleTxUuid{"0000ffe1-0000-1000-8000-00805f9b34fb"};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::Config;
using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Populates models with hardcoded defaults and persists them.
///
/// This method is typically called when no configuration file is found
/// or when a factory reset of the configuration is required.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::defaultConfigStore() {
    populateDefaults();
    store();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Populates models with default values.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::populateDefaults() {
    // Set default control configuration
    const auto enableKey = m_config->toString(ModelControlKey::Enable);
    m_config->add(enableKey, cConfigDefaultControlEnable.data());
    const auto modeKey = m_config->toString(ModelControlKey::Mode);
    m_config->add(modeKey, cConfigDefaultControlMode.data());
    const auto toggleKey = m_config->toString(ModelControlKey::Toggle);
    m_config->add(toggleKey, cConfigDefaultControlToggle.data());
    const auto timerKey = m_config->toString(ModelControlKey::Timer);
    m_config->add(timerKey, cConfigDefaultControlTimer.data());
    const auto timerEnableKey =
        m_config->toString(ModelControlKey::TimerEnable);
    m_config->add(timerEnableKey, cConfigDefaultControlTimerEnable.data());

    // Set default serial configuration
    const auto deviceKey = m_config->toString(ModelSerialKey::Device);
    m_config->add(deviceKey, cConfigDefaultSerialDevice.data());
    const auto baudKey = m_config->toString(ModelSerialKey::Baud);
    m_config->add(baudKey, cConfigDefaultSerialBaud.data());
    const auto dataKey = m_config->toString(ModelSerialKey::Data);
    m_config->add(dataKey, cConfigDefaultSerialData.data());
    const auto parityKey = m_config->toString(ModelSerialKey::Parity);
    m_config->add(parityKey, cConfigDefaultSerialParity.data());
    const auto stopKey = m_config->toString(ModelSerialKey::Stop);
    m_config->add(stopKey, cConfigDefaultSerialStop.data());
    const auto flowKey = m_config->toString(ModelSerialKey::Flow);
    m_config->add(flowKey, cConfigDefaultSerialFlow.data());

    // Set default log configuration
    const auto filePathKey = m_config->toString(ModelLogKey::FilePath);
    m_config->add(filePathKey, cConfigDefaultLogFilePath.data());
    const auto logLevelKey = m_config->toString(ModelLogKey::LogLevel);
    m_config->add(logLevelKey, cConfigDefaultLogLevel.data());

    // Set default general configuration
    const auto comTypeKey = m_config->toString(ModelGeneralKey::ComType);
    m_config->add(comTypeKey, cConfigDefaultGeneralComType.data());
    const auto tcpIpKey = m_config->toString(ModelGeneralKey::TcpIp);
    m_config->add(tcpIpKey, cConfigDefaultGeneralTcpIp.data());
    const auto tcpPortKey = m_config->toString(ModelGeneralKey::TcpPort);
    m_config->add(tcpPortKey, cConfigDefaultGeneralTcpPort.data());

    // Set default BLE configuration
    const auto bleAddrKey = m_config->toString(ModelBleKey::Address);
    m_config->add(bleAddrKey, cConfigDefaultBleAddress.data());
    const auto bleServiceKey = m_config->toString(ModelBleKey::ServiceUuid);
    m_config->add(bleServiceKey, cConfigDefaultBleServiceUuid.data());
    const auto bleRxKey = m_config->toString(ModelBleKey::RxUuid);
    m_config->add(bleRxKey, cConfigDefaultBleRxUuid.data());
    const auto bleTxKey = m_config->toString(ModelBleKey::TxUuid);
    m_config->add(bleTxKey, cConfigDefaultBleTxUuid.data());
}
