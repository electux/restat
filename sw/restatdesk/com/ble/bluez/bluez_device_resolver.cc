////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_device_resolver.cc
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

#include <com/ble/bluez/bluez_device_resolver.h>
#include <map>

using namespace Electux::App::Com;

namespace {
    Glib::ustring get_string_from_variant(const Glib::VariantBase& var) {
        gsize length = 0;
        const gchar* str = g_variant_get_string(const_cast<GVariant*>(var.gobj()), &length); // NOLINT(cppcoreguidelines-pro-type-const-cast)
        return Glib::ustring(str, length);
    }

    Glib::ustring getStringProperty(const Glib::VariantBase& propValVar) {
        GVariant* innerGVar = g_variant_get_variant(const_cast<GVariant*>(propValVar.gobj())); // NOLINT(cppcoreguidelines-pro-type-const-cast)
        Glib::VariantBase inner(innerGVar, true);
        return get_string_from_variant(inner);
    }
    constexpr const char* cDeviceInterface{"org.bluez.Device1"};
    constexpr const char* cAddressProp{"Address"};
    constexpr const char* cGattCharacteristicInterface{"org.bluez.GattCharacteristic1"};
    constexpr const char* cUuidProp{"UUID"};
    constexpr const char* cServiceProp{"Service"};
    constexpr const char* cGattServiceInterface{"org.bluez.GattService1"};
    constexpr const char* cDeviceProp{"Device"};
} // namespace

Glib::ustring BluezDeviceResolver::findDevicePath(
    const Glib::VariantContainerBase &objectsBase, 
    const std::string &address
) {
    size_t nObjects = objectsBase.get_n_children();
    for (size_t i = 0; i < nObjects; ++i) {
        Glib::VariantContainerBase objEntry;
        objectsBase.get_child(objEntry, i);

        Glib::ustring path = get_string_from_variant(objEntry.get_child(0));

        Glib::VariantContainerBase interfacesVar = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(objEntry.get_child(1));
        size_t nInterfaces = interfacesVar.get_n_children();
        for (size_t j = 0; j < nInterfaces; ++j) {
            Glib::VariantContainerBase intEntry;
            interfacesVar.get_child(intEntry, j);

            Glib::ustring interfaceName = get_string_from_variant(intEntry.get_child(0));

            if (interfaceName == cDeviceInterface) {
                Glib::VariantContainerBase propertiesVar = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(intEntry.get_child(1));
                size_t nProps = propertiesVar.get_n_children();
                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);

                    Glib::ustring propName = get_string_from_variant(propEntry.get_child(0));

                    if (propName == cAddressProp) {
                        Glib::VariantBase propValBase = propEntry.get_child(1);
                        GVariant* innerGVar = g_variant_get_variant(const_cast<GVariant*>(propValBase.gobj()));
                        Glib::VariantBase inner(innerGVar, true);
                        Glib::ustring addr = get_string_from_variant(inner);
                        if (g_ascii_strcasecmp(addr.c_str(), address.c_str()) == 0) {
                            return path;
                        }
                    }
                }
            }
        }
    }
    return "";
}

bool BluezDeviceResolver::findGattPaths(
    const Glib::VariantContainerBase &objectsBase,
    const Glib::ustring &devicePath,
    const std::string &serviceUuid,
    const std::string &rxUuid,
    const std::string &txUuid,
    Glib::ustring &rxPath,
    Glib::ustring &txPath
) {
    struct CharInfo {
        Glib::ustring uuid;
        Glib::ustring servicePath;
    };
    std::map<Glib::ustring, CharInfo> characteristics;
    std::map<Glib::ustring, Glib::ustring> servicePathToUuid;
    std::map<Glib::ustring, Glib::ustring> servicePathToDevice;

    size_t nObjects = objectsBase.get_n_children();
    for (size_t i = 0; i < nObjects; ++i) {
        Glib::VariantContainerBase objEntry;
        objectsBase.get_child(objEntry, i);

        Glib::ustring path = get_string_from_variant(objEntry.get_child(0));

        Glib::VariantContainerBase interfacesVar = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(objEntry.get_child(1));
        size_t nInterfaces = interfacesVar.get_n_children();
        for (size_t j = 0; j < nInterfaces; ++j) {
            Glib::VariantContainerBase intEntry;
            interfacesVar.get_child(intEntry, j);

            Glib::ustring interfaceName = get_string_from_variant(intEntry.get_child(0));

            if (interfaceName == cGattCharacteristicInterface) {
                Glib::VariantContainerBase propertiesVar = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(intEntry.get_child(1));
                size_t nProps = propertiesVar.get_n_children();
                CharInfo info;
                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);

                    Glib::ustring propName = get_string_from_variant(propEntry.get_child(0));

                    if (propName == cUuidProp) {
                        info.uuid = getStringProperty(propEntry.get_child(1));
                    } else if (propName == cServiceProp) {
                        info.servicePath = getStringProperty(propEntry.get_child(1));
                    }
                }
                characteristics[path] = info;
            } else if (interfaceName == cGattServiceInterface) {
                Glib::VariantContainerBase propertiesVar = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(intEntry.get_child(1));
                size_t nProps = propertiesVar.get_n_children();
                Glib::ustring uuid;
                Glib::ustring devPath;
                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);

                    Glib::ustring propName = get_string_from_variant(propEntry.get_child(0));

                    if (propName == cUuidProp) {
                        uuid = getStringProperty(propEntry.get_child(1));
                    } else if (propName == cDeviceProp) {
                        devPath = getStringProperty(propEntry.get_child(1));
                    }
                }
                servicePathToUuid[path] = uuid;
                servicePathToDevice[path] = devPath;
            }
        }
    }

    rxPath.clear();
    txPath.clear();
    for (const auto& [path, info] : characteristics) {
        Glib::ustring servicePath = info.servicePath;
        if (servicePathToDevice[servicePath] == devicePath) {
            Glib::ustring serviceUuid_found = servicePathToUuid[servicePath];
            if (g_ascii_strcasecmp(serviceUuid_found.c_str(), serviceUuid.c_str()) == 0) {
                if (g_ascii_strcasecmp(info.uuid.c_str(), rxUuid.c_str()) == 0) {
                    rxPath = path;
                }
                if (g_ascii_strcasecmp(info.uuid.c_str(), txUuid.c_str()) == 0) {
                    txPath = path;
                }
            }
        }
    }

    return !rxPath.empty() && !txPath.empty();
}
