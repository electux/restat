////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// config_manager.cc
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
#include <filesystem>
#include <fstream>
#include <glibmm/miscutils.h>
#include <iostream>
#include <memory>
#include <model/model_factory.h>
#include <sstream>

namespace {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Internal Configuration Constants
    /// @{
    // Default values for Control Model
    constexpr std::string_view cConfigFile{".restat/config"};
    // Delimiter for key-value pairs in the config file
    constexpr char cConfigAssignDelimiter{'='};
    // Character indicating a comment line in the config file
    constexpr char cConfigCommentChar{'#'};
    // Console messages
    constexpr std::string_view cUnableToCreateFileMsg{"Unable to create file: "};
    constexpr std::string_view cInitConfigPathMsg{"Initialized configuration file path: "};
    constexpr std::string_view cInitErrorMsg{"Error during ConfigManager initialization: "};
    constexpr std::string_view cLoadingConfigMsg{"Loading configuration..."};
    constexpr std::string_view cUnableToOpenFileMsg{"Unable to open file: "};
    constexpr std::string_view cUnknownKeyWarningMsg{"Warning: Unknown configuration key: "};
    constexpr std::string_view cLoadConfigDoneMsg{"Load configuration done."};
    constexpr std::string_view cStoringConfigMsg{"Storing configuration..."};
    constexpr std::string_view cStoreConfigDoneMsg{"Store configuration done."};
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

using namespace Electux::App::Config;
using namespace Electux::App::Model;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructor that initializes the config path.
/// @param configFileName The path/name of the configuration file.
////////////////////////////////////////////////////////////////////////////////////////////////////////
ConfigManager::ConfigManager(
    std::unique_ptr<Electux::App::Model::IModel> config,
    const std::string &configFileName,
    bool verbose
) : m_verbose(verbose), m_config(std::move(config)) {
    m_fileName =
        configFileName.empty()
            ? Glib::build_filename(Glib::get_home_dir(), cConfigFile.data())
            : configFileName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief ConfigManager destructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////
ConfigManager::~ConfigManager() = default;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Initializes the configuration manager.
/// Performs file system checks, directory creation, and initial load.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::init() {
    populateDefaults();

    auto dirPath = Glib::path_get_dirname(m_fileName);

    try {
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directories(dirPath);
        }

        if (!std::filesystem::exists(m_fileName)) {
            {
                std::ofstream file(m_fileName);
                if (!file) {
                    throw std::ios_base::failure(
                        std::string(cUnableToCreateFileMsg) + m_fileName
                    );
                }

                // File closes here when going out of scope, releasing the
                // handle before store()
            }
            defaultConfigStore();
        }

        if (m_verbose) {
            std::cout << cInitConfigPathMsg << m_fileName
                      << std::endl;
        }
        load();
    } catch (const std::exception &e) {
        std::cerr << cInitErrorMsg << e.what()
                  << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Parses the configuration file line by line.
///
/// Skips comments and empty lines. Validates keys against models.
/// @return true if the configuration was successfully loaded, else false.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConfigManager::load() {
    std::ifstream file(m_fileName);
    if (m_verbose) {
        std::cout << cLoadingConfigMsg << std::endl;
    }

    if (!file.is_open()) {
        std::cerr << cUnableToOpenFileMsg << m_fileName << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == cConfigCommentChar) {
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if (std::getline(iss, key, cConfigAssignDelimiter) &&
            std::getline(iss, value)) {
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t\n\r"));
            key.erase(key.find_last_not_of(" \t\n\r") + 1);
            value.erase(0, value.find_first_not_of(" \t\n\r"));
            value.erase(value.find_last_not_of(" \t\n\r") + 1);

            // Map keys to specific models
            if (m_config->validateKey(key)) {
                if (!m_config->update(key, value)) {
                    m_config->add(key, value);
                }
            } else {
                std::cerr << cUnknownKeyWarningMsg << key
                          << std::endl;
                continue;
            }
        }
    }

    file.close();
    if (m_verbose) {
        std::cout << cLoadConfigDoneMsg << std::endl;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Serializes all models and writes them to the configuration file.
/// @return true if the configuration was successfully stored, else false.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConfigManager::store(bool forceVerbose) {
    std::ofstream file(m_fileName);
    bool shouldPrint = forceVerbose && m_verbose;
    if (shouldPrint) {
        std::cout << cStoringConfigMsg << std::endl;
    }

    if (!file.is_open()) {
        std::cerr << cUnableToOpenFileMsg << m_fileName << std::endl;
        return false;
    }

    // Internal helper lambda for writing model entries
    auto writeModel = [&](const auto &model) {
        for (const auto &[key, value] : model.getAllEntries()) {
            file << key << cConfigAssignDelimiter << value << "\n";
        }
    };

    writeModel(*m_config);

    file.close();
    if (shouldPrint) {
        std::cout << cStoreConfigDoneMsg << std::endl;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the control configuration.
/// @param config Reference to the Model configuration object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConfigManager::setConfig(const Electux::App::Model::IModel &config) {
    m_config = config.clone();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Gets the current control configuration.
/// @return A constant reference to the Model configuration.
////////////////////////////////////////////////////////////////////////////////////////////////////////
const Electux::App::Model::IModel &ConfigManager::getConfig() const {
    return *m_config;
}
