////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// imodel.h
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
#pragma once

#include <cstdint>
#include <map>
#include <model/channel_state.h>
#include <model/model_types.h>
#include <sigc++/sigc++.h>
#include <string>
#include <string_view>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Model
/// @brief Namespace for application data models and entities
namespace Electux::App::Model {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @name Local Type Aliases
    /// @{
    using Entities = std::map<std::string, std::string, std::less<>>;
    using ChannelState = Electux::App::Model::Channel::ChannelState;
    /// @}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IModel
    /// @brief Interface for application data models.
    ///
    /// Defines core operations for managing key-value pairs representing
    /// configuration or state data within the application.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IEntityModel {
      public:
        virtual ~IEntityModel() = default;

        virtual bool
        add(const std::string_view &key, const std::string_view &data) = 0;

        virtual bool validateKey(const std::string_view &key) const = 0;

        virtual const std::string &getEntity(const std::string_view &key
        ) const = 0;

        virtual bool
        update(const std::string_view &key, const std::string_view &data) = 0;

        virtual const Entities &get() const = 0;

        virtual Entities getAllEntries() const = 0;

        virtual void clear() = 0;

        virtual sigc::signal<void()> signal_changed() const = 0;

        virtual void emit_changed() const = 0;
    };

    class IControlModel {
      public:
        virtual ~IControlModel() = default;

        virtual ChannelState getChannelState(size_t index) const = 0;

        virtual void
        setChannelState(size_t index, const ChannelState &state) = 0;

        virtual std::string_view toString(ModelControlKey key) const = 0;
    };

    class ISerialModel {
      public:
        virtual ~ISerialModel() = default;

        virtual std::string_view toString(ModelSerialKey key) const = 0;
    };

    class IBleModel {
      public:
        virtual ~IBleModel() = default;

        virtual std::string_view toString(ModelBleKey key) const = 0;
    };

    class ILogModel {
      public:
        virtual ~ILogModel() = default;

        virtual std::string_view toString(ModelLogKey key) const = 0;
    };

    class IGeneralModel {
      public:
        virtual ~IGeneralModel() = default;

        virtual std::string_view toString(ModelGeneralKey key) const = 0;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IModel
    /// @brief Interface for application data models, inheriting from segregated sub-interfaces.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IModel : public IEntityModel,
                   public IControlModel,
                   public ISerialModel,
                   public IBleModel,
                   public ILogModel,
                   public IGeneralModel {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor for the IModel interface.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        inline ~IModel() noexcept override = default;

        using IControlModel::toString;
        using ISerialModel::toString;
        using IBleModel::toString;
        using ILogModel::toString;
        using IGeneralModel::toString;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Polymorphic deep copy of the model.
        /// @return A unique_ptr containing the cloned IModel.
        ////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::unique_ptr<IModel> clone() const = 0;
    };
} // namespace Electux::App::Model
