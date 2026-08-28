////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// model.h
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

#include <model/imodel.h>
#include <model/delegate/control/icontrol_model_delegate.h>
#include <model/delegate/serial/iserial_model_delegate.h>
#include <model/delegate/general/igeneral_model_delegate.h>
#include <model/delegate/ble/ible_model_delegate.h>
#include <model/delegate/log/ilog_model_delegate.h>
#include <memory>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Model
/// @brief Namespace for application data models and entities
namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class Model
    /// @brief Concrete implementation of the IModel interface.
    ///
    /// Provides a standard container for managing application entities using
    /// an internal map-based storage mechanism.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class Model : public IModel {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Model constructor with Dependency Injection.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        Model(
            std::unique_ptr<IControlModelDelegate> controlDelegate,
            std::unique_ptr<ISerialModelDelegate> serialDelegate,
            std::unique_ptr<IGeneralModelDelegate> generalDelegate,
            std::unique_ptr<IBleModelDelegate> bleDelegate,
            std::unique_ptr<ILogModelDelegate> logDelegate
        ) noexcept;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Model copy constructor to support deep cloning.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        Model(const Model &other);

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds an entity to the model.
        /// @param key Represents the model entity key to be added.
        /// @param data Represents the model entity data to be added.
        /// @return true if the entity was successfully added, false otherwise.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool
        add(const std::string_view &key, const std::string_view &data) final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Validates if a string key is a valid serial configuration
        /// key.
        /// @param key Represents the string key to be validated.
        /// @return true if the key is valid, false otherwise.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool validateKey(const std::string_view &key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets an entity value by its key.
        /// @param key Represents the model entity key.
        /// @return Reference to the string entity selected by key.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string &getEntity(const std::string_view &key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets all model entities.
        /// @return Constant reference to the map of strings {key: data}.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        const Entities &get() const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets a copy of all serial model entries.
        /// @return A map containing all serial configuration entries {key:
        /// data}.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        Entities getAllEntries() const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Updates an entity value by its key.
        /// @param key Represents the model entity key.
        /// @param data Represents the new value for the entity.
        /// @return true if the entity was updated, false if the key does not
        /// exist.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        bool
        update(const std::string_view &key, const std::string_view &data) final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Clears all model entities.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        void clear() final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the state of a specific channel.
        /// @param index The index of the channel.
        /// @return The ChannelState representation of the channel status.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        ChannelState getChannelState(size_t index) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the state of a specific channel.
        /// @param index The index of the channel.
        /// @param state The new ChannelState value.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        void setChannelState(size_t index, const ChannelState &state) final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts a ModelSerialKey enum value to its string
        /// representation.
        /// @param key Represents the ModelSerialKey enum value.
        /// @return A string_view containing the key name.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::string_view toString(const ModelSerialKey key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts a ModelGeneralKey enum value to its string
        /// representation.
        /// @param key Represents the ModelGeneralKey enum value.
        /// @return A string_view containing the key name.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::string_view toString(const ModelGeneralKey key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts a ModelBleKey enum value to its string
        /// representation.
        /// @param key Represents the ModelBleKey enum value.
        /// @return A string_view containing the key name.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::string_view toString(const ModelBleKey key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts a ModelLogKey enum value to its string
        /// representation.
        /// @param key Represents the ModelLogKey enum value.
        /// @return A string_view containing the key name.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::string_view toString(const ModelLogKey key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts a ModelControlKey enum value to its string
        /// representation.
        /// @param key Represents the ModelControlKey enum value.
        /// @return A string_view containing the key name.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::string_view toString(const ModelControlKey key) const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a signal that is emitted when the model data changes.
        /// @return A signal object that can be connected to a callback.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        sigc::signal<void()> signal_changed() const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Emits the changed signal.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        void emit_changed() const final;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a deep copy of the model.
        /// @return A unique_ptr to a new instance of the model.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<IModel> clone() const final;

      private:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Internal storage for model entities in map format {key:
        /// data}.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        Entities m_entities{};
        mutable sigc::signal<void()> m_signalChanged{};

        std::unique_ptr<IControlModelDelegate> m_controlDelegate;
        std::unique_ptr<ISerialModelDelegate> m_serialDelegate;
        std::unique_ptr<IGeneralModelDelegate> m_generalDelegate;
        std::unique_ptr<IBleModelDelegate> m_bleDelegate;
        std::unique_ptr<ILogModelDelegate> m_logDelegate;
    };
} // namespace Electux::App::Model
