////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.cc
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

#include <app_controller.h>
#include <chrono>
#include <com/icom.h>
#include <com/icom_configurator.h>
#include <com/switchable_com.h>
#include <command/formatter/icommand_formatter.h>
#include <command/processor/response_processor.h>
#include <config/iconfig.h>
#include <format>
#include <log/ilog.h>
#include <model/model.h>
#include <string>
#include <vector>

using namespace Electux::App;

namespace {
    constexpr std::chrono::milliseconds cThreadSleepDuration{100};
} // namespace

AppController::AppController(
    std::unique_ptr<Config::IConfig> configManager,
    std::unique_ptr<Com::ICom> comChannel,
    std::unique_ptr<Com::IComConfigurator> comConfigurator,
    std::unique_ptr<Logger::ILog> logger,
    std::unique_ptr<Command::ICommandFormatter> commandFormatter,
    std::unique_ptr<Command::IResponseProcessor> responseProcessor
)
    : m_configManager(std::move(configManager)),
      m_comChannel(std::move(comChannel)),
      m_comConfigurator(std::move(comConfigurator)),
      m_logger(std::move(logger)),
      m_commandFormatter(std::move(commandFormatter)),
      m_responseProcessor(std::move(responseProcessor)) {}

AppController::~AppController() {
    m_stopThread = true;
    if (m_readThread.joinable()) {
        m_readThread.join();
    }
    if (m_comChannel) {
        m_comChannel->close();
    }
}

void AppController::startup() {
    m_configManager->init();
    configureLogger();
    configureComChannel();

    m_stopThread = false;
    m_readThread = std::thread(&AppController::readLoop, this);

    m_logger->log("Application started.", Logger::LogLevel::Info);

    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmdBoardId = m_commandFormatter->getCommandBoardId();

        if (!cmdBoardId.empty()) {
            std::vector<uint8_t> cmdBytes(cmdBoardId.begin(), cmdBoardId.end());
            m_comChannel->write(cmdBytes);
        }

        std::string cmdVersion = m_commandFormatter->getCommandVersion();

        if (!cmdVersion.empty()) {
            std::vector<uint8_t> cmdBytes(cmdVersion.begin(), cmdVersion.end());
            m_comChannel->write(cmdBytes);
        }

        std::string cmdAllStat =
            m_commandFormatter->getCommandStatusAllChannels();

        if (!cmdAllStat.empty()) {
            std::vector<uint8_t> cmdBytes(cmdAllStat.begin(), cmdAllStat.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::turnOnAllChannels() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandOnAllChannels();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::turnOffAllChannels() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandOffAllChannels();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::requestAllChannelsStatus() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandStatusAllChannels();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::resetSystem() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandReset();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            m_comChannel->close();
        }
    }
}

void AppController::requestBoardId() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandBoardId();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::requestVersion() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmd = m_commandFormatter->getCommandVersion();
        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::shutdown() {
    m_stopThread = true;

    if (m_readThread.joinable()) {
        m_readThread.join();
    }

    if (m_comChannel) {
        m_comChannel->close();
    }

    if (m_logger) {
        m_logger->log("Application shutting down.", Logger::LogLevel::Info);
        m_logger->close();
    }

    m_configManager->store(true);
}

void AppController::configureLogger() {
    if (!m_logger) {
        return;
    }

    m_logger->close();

    auto &config = getModel();
    auto pathKey = config.toString(Model::ModelLogKey::FilePath);
    auto levelKey = config.toString(Model::ModelLogKey::LogLevel);

    m_logger->setOutputFile(config.getEntity(pathKey));

    uint32_t levelIdx =
        static_cast<uint32_t>(std::stoul(config.getEntity(levelKey)));
    m_logger->setLevel(static_cast<Logger::LogLevel>(levelIdx));

    m_logger->open();
}

void AppController::configureComChannel() {
    if (!m_comChannel || !m_comConfigurator) {
        return;
    }

    m_comChannel->close();
    m_comConfigurator->configure(getModel(), m_comChannel.get());
}

const Model::IModel &AppController::getModel() const {
    return m_configManager->getConfig();
}

void AppController::onSetupChanged(const Model::SettingsSetup &setup) {
    const auto &oldConfig = m_configManager->getConfig();
    auto &newConfig = *setup.m_config;

    bool logChanged = hasLoggerConfigChanged(oldConfig, newConfig);
    bool comChanged = hasSerialConfigChanged(oldConfig, newConfig) ||
                      hasGeneralConfigChanged(oldConfig, newConfig) ||
                      hasBleConfigChanged(oldConfig, newConfig);

    m_configManager->setConfig(newConfig);
    m_configManager->store();

    if (logChanged) {
        configureLogger();
    }

    if (comChanged) {
        configureComChannel();
    }

    getModel().emit_changed();
}

void AppController::executePlan() {
    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::vector<Model::Channel::ChannelState> states;
        for (size_t i = 0; i < Model::Channel::cNumOfChannels; ++i) {
            states.push_back(getModel().getChannelState(i));
        }
        std::string cmd = m_commandFormatter->getCommandPlan(states);
        if (!cmd.empty()) {
            m_logger->log("Executing variable plan on channel: " + cmd, Logger::LogLevel::Info);
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());
            m_comChannel->write(cmdBytes);
            m_signalDataReceived.emit(cmd);
        }
    }
}



bool AppController::hasSerialConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelSerialKey::Device);
         k <= static_cast<int>(Model::ModelSerialKey::Flow); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelSerialKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasLoggerConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelLogKey::FilePath);
         k <= static_cast<int>(Model::ModelLogKey::LogLevel); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelLogKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasGeneralConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelGeneralKey::ComType);
         k <= static_cast<int>(Model::ModelGeneralKey::TcpPort); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelGeneralKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasBleConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelBleKey::Address);
         k <= static_cast<int>(Model::ModelBleKey::TxUuid); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelBleKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

sigc::signal<void(const std::string &)> AppController::signal_data_received() {
    return m_signalDataReceived;
}

void AppController::readLoop() {
    while (!m_stopThread) {
        try {
            if (m_comChannel && m_comChannel->isOpen()) {
                std::vector<uint8_t> buffer;
                m_comChannel->read(buffer, 1);

                if (!m_stopThread && !m_comChannel->isOpen()) {
                    std::string errorMsg = "\n[Error] Connection lost.";
                    auto *switchable =
                        dynamic_cast<Com::SwitchableCom *>(m_comChannel.get());
                    if (switchable) {
                        if (switchable->getActiveCom() ==
                            switchable->getSerialCom()) {
                            errorMsg =
                                "\n[Error] Serial port is no longer available "
                                "(I/O error). Device disconnected.";
                        } else if (
                            switchable->getActiveCom() ==
                            switchable->getTcpCom()
                        ) {
                            errorMsg =
                                "\n[Error] TCP connection lost (I/O error).";
                        } else if (
                            switchable->getActiveCom() ==
                            switchable->getBleCom()
                        ) {
                            errorMsg =
                                "\n[Error] BLE connection lost (I/O error).";
                        }
                    }
                    m_signalDataReceived.emit(errorMsg);
                    if (m_logger) {
                        m_logger->log(
                            "Communication channel lost (I/O error).",
                            Logger::LogLevel::Error
                        );
                    }
                } else if (!buffer.empty()) {
                    std::string dataStr(buffer.begin(), buffer.end());

                    if (m_responseProcessor) {
                        auto payloads = m_responseProcessor->process(dataStr);

                        for (const auto &payload : payloads) {
                            m_signalDataReceived.emit(payload);
                        }

                    } else {
                        m_signalDataReceived.emit(dataStr);
                    }
                }

            } else {
                static auto lastReconnectTry = std::chrono::steady_clock::now();
                auto now = std::chrono::steady_clock::now();
                if (now - lastReconnectTry >= std::chrono::seconds(2)) {
                    lastReconnectTry = now;
                    if (m_logger) {
                        m_logger->log(
                            "Communication channel closed. Attempting to "
                            "reconnect...",
                            Logger::LogLevel::Warning
                        );
                    }
                    configureComChannel();
                }
                std::this_thread::sleep_for(cThreadSleepDuration);
            }
        } catch (...) {
            std::this_thread::sleep_for(cThreadSleepDuration);
        }
    }
}
