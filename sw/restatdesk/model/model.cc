////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// model.cc
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

#include <algorithm>
#include <model/model.h>
#include <vector>

namespace Electux::App::Model {
    constexpr std::string_view cFallback{""};
} // namespace Electux::App::Model

using namespace Electux::App::Model;

Model::Model(
    std::unique_ptr<IControlModelDelegate> controlDelegate,
    std::unique_ptr<ISerialModelDelegate> serialDelegate,
    std::unique_ptr<IGeneralModelDelegate> generalDelegate,
    std::unique_ptr<IBleModelDelegate> bleDelegate,
    std::unique_ptr<ILogModelDelegate> logDelegate
) noexcept
    : m_controlDelegate(std::move(controlDelegate)),
      m_serialDelegate(std::move(serialDelegate)),
      m_generalDelegate(std::move(generalDelegate)),
      m_bleDelegate(std::move(bleDelegate)),
      m_logDelegate(std::move(logDelegate)) {}

Model::Model(const Model &other)
    : m_entities(other.m_entities),
      m_controlDelegate(other.m_controlDelegate ? other.m_controlDelegate->clone() : nullptr),
      m_serialDelegate(other.m_serialDelegate ? other.m_serialDelegate->clone() : nullptr),
      m_generalDelegate(other.m_generalDelegate ? other.m_generalDelegate->clone() : nullptr),
      m_bleDelegate(other.m_bleDelegate ? other.m_bleDelegate->clone() : nullptr),
      m_logDelegate(other.m_logDelegate ? other.m_logDelegate->clone() : nullptr) {}

bool Model::add(const std::string_view &key, const std::string_view &data) {
    if (m_entities.find(key) != m_entities.end()) {
        return false;
    }
    auto [it, inserted] =
        m_entities.emplace(std::string(key), std::string(data));
    return inserted;
}

bool Model::validateKey(const std::string_view &key) const {
    return (m_controlDelegate && m_controlDelegate->validateKey(key)) ||
           (m_serialDelegate && m_serialDelegate->validateKey(key)) ||
           (m_generalDelegate && m_generalDelegate->validateKey(key)) ||
           (m_bleDelegate && m_bleDelegate->validateKey(key)) ||
           (m_logDelegate && m_logDelegate->validateKey(key));
}

const std::string &Model::getEntity(const std::string_view &key) const {
    auto it = m_entities.find(key);
    if (it != m_entities.end()) {
        return it->second;
    }
    static const std::string fallback{cFallback.data(), cFallback.size()};
    return fallback;
}

const Entities &Model::get() const { return m_entities; }

Entities Model::getAllEntries() const {
    Entities entries;

    auto fill = [&](auto &&keys, const auto &delegate) {
        if (!delegate) return;
        for (const auto &key : keys) {
            std::string keyStr{delegate->toString(key)};
            entries.emplace(std::move(keyStr), getEntity(keyStr));
        }
    };

    static const std::vector<ModelControlKey> controlKeys = {
        ModelControlKey::Enable, ModelControlKey::Mode, ModelControlKey::Toggle,
        ModelControlKey::Timer, ModelControlKey::TimerEnable
    };

    static const std::vector<ModelLogKey> logKeys = {
        ModelLogKey::LogLevel, ModelLogKey::FilePath
    };

    static const std::vector<ModelSerialKey> serialKeys = {
        ModelSerialKey::Device, ModelSerialKey::Baud, ModelSerialKey::Data,
        ModelSerialKey::Parity, ModelSerialKey::Stop, ModelSerialKey::Flow
    };

    static const std::vector<ModelGeneralKey> generalKeys = {
        ModelGeneralKey::ComType, ModelGeneralKey::TcpIp, ModelGeneralKey::TcpPort
    };

    static const std::vector<ModelBleKey> bleKeys = {
        ModelBleKey::Address, ModelBleKey::ServiceUuid,
        ModelBleKey::RxUuid, ModelBleKey::TxUuid
    };

    fill(controlKeys, m_controlDelegate);
    fill(logKeys, m_logDelegate);
    fill(serialKeys, m_serialDelegate);
    fill(generalKeys, m_generalDelegate);
    fill(bleKeys, m_bleDelegate);

    return entries;
}

bool Model::update(const std::string_view &key, const std::string_view &data) {
    auto it = m_entities.find(key);
    if (it != m_entities.end()) {
        it->second = data;
        return true;
    }
    return false;
}

void Model::clear() { m_entities.clear(); }

std::string_view Model::toString(const ModelControlKey key) const {
    return m_controlDelegate ? m_controlDelegate->toString(key) : "";
}

std::string_view Model::toString(const ModelLogKey key) const {
    return m_logDelegate ? m_logDelegate->toString(key) : "";
}

std::string_view Model::toString(const ModelSerialKey key) const {
    return m_serialDelegate ? m_serialDelegate->toString(key) : "";
}

std::string_view Model::toString(const ModelGeneralKey key) const {
    return m_generalDelegate ? m_generalDelegate->toString(key) : "";
}

std::string_view Model::toString(const ModelBleKey key) const {
    return m_bleDelegate ? m_bleDelegate->toString(key) : "";
}

ChannelState Model::getChannelState(size_t index) const {
    return m_controlDelegate ? m_controlDelegate->getChannelState(m_entities, index) : ChannelState{};
}

void Model::setChannelState(size_t index, const ChannelState &state) {
    if (m_controlDelegate) {
        m_controlDelegate->setChannelState(m_entities, index, state);
    }
}

sigc::signal<void()> Model::signal_changed() const { return m_signalChanged; }

void Model::emit_changed() const { m_signalChanged.emit(); }

std::unique_ptr<IModel> Model::clone() const {
    return std::make_unique<Model>(*this);
}
