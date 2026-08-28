# -*- coding: UTF-8 -*-

'''
Module
    run-ble.py
Copyright
    Copyright (C) 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
    restat is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    restat is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    A D-Bus mock server script to simulate a BLE device for testing.
'''

from __future__ import annotations

from sys import stdin, exit as sys_exit, argv
from termios import tcgetattr, tcsetattr, TCSADRAIN
from tty import setcbreak
from select import select
from time import sleep, strftime
import argparse
import threading

try:
    import dbus
    import dbus.service
    import dbus.mainloop.glib
    from gi.repository import GLib
except ImportError:
    print("Error: Missing dependencies. Please install dbus-python and PyGObject:")
    print("  sudo apt install python3-dbus python3-gi")
    sys_exit(1)

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/restat'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/restat/blob/dev/LICENSE'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'

# Default configuration values
DEFAULT_MAC = "00:11:22:33:44:55"
DEFAULT_SERVICE_UUID = "0000ffe0-0000-1000-8000-00805f9b34fb"
DEFAULT_RX_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"
DEFAULT_TX_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb"


class DeviceObject(dbus.service.Object):
    def __init__(self, bus, path, address):
        super().__init__(bus, path)
        self.path = path
        self.address = address
        self.connected = False
        self.services_resolved = True

    @dbus.service.method('org.bluez.Device1', in_signature='', out_signature='')
    def Connect(self):
        print(f"[{strftime('%H:%M:%S')}] [Device] Connect called on {self.path}")
        self.connected = True
        self.PropertiesChanged('org.bluez.Device1', {'Connected': dbus.Boolean(True)}, [])

    @dbus.service.method('org.bluez.Device1', in_signature='', out_signature='')
    def Disconnect(self):
        print(f"[{strftime('%H:%M:%S')}] [Device] Disconnect called on {self.path}")
        self.connected = False
        self.PropertiesChanged('org.bluez.Device1', {'Connected': dbus.Boolean(False)}, [])

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='ss', out_signature='v')
    def Get(self, interface, prop):
        if interface == 'org.bluez.Device1':
            if prop == 'Address':
                return dbus.String(self.address)
            elif prop == 'Connected':
                return dbus.Boolean(self.connected)
            elif prop == 'ServicesResolved':
                return dbus.Boolean(self.services_resolved)
        raise dbus.exceptions.DBusException('org.freedesktop.DBus.Error.InvalidArgs')

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface):
        if interface == 'org.bluez.Device1':
            return {
                'Address': dbus.String(self.address),
                'Connected': dbus.Boolean(self.connected),
                'ServicesResolved': dbus.Boolean(self.services_resolved)
            }
        return {}

    @dbus.service.signal('org.freedesktop.DBus.Properties', signature='sa{sv}as')
    def PropertiesChanged(self, interface, changed, invalidated):
        pass


class GattServiceObject(dbus.service.Object):
    def __init__(self, bus, path, uuid, device_path):
        super().__init__(bus, path)
        self.path = path
        self.uuid = uuid
        self.device_path = device_path

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='ss', out_signature='v')
    def Get(self, interface, prop):
        if interface == 'org.bluez.GattService1':
            if prop == 'UUID':
                return dbus.String(self.uuid)
            elif prop == 'Device':
                return dbus.ObjectPath(self.device_path)
        raise dbus.exceptions.DBusException('org.freedesktop.DBus.Error.InvalidArgs')

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface):
        if interface == 'org.bluez.GattService1':
            return {
                'UUID': dbus.String(self.uuid),
                'Device': dbus.ObjectPath(self.device_path)
            }
        return {}


class GattCharacteristicObject(dbus.service.Object):
    def __init__(self, bus, path, uuid, service_path, is_rx=False):
        super().__init__(bus, path)
        self.path = path
        self.uuid = uuid
        self.service_path = service_path
        self.is_rx = is_rx
        self.notifying = False
        self.value = []
        self.rx_partner = None

    @dbus.service.method('org.bluez.GattCharacteristic1', in_signature='', out_signature='')
    def StartNotify(self):
        print(f"[{strftime('%H:%M:%S')}] [Characteristic] StartNotify called on {self.path} (UUID: {self.uuid})")
        self.notifying = True
        self.PropertiesChanged('org.bluez.GattCharacteristic1', {'Notifying': dbus.Boolean(True)}, [])

    @dbus.service.method('org.bluez.GattCharacteristic1', in_signature='', out_signature='')
    def StopNotify(self):
        print(f"[{strftime('%H:%M:%S')}] [Characteristic] StopNotify called on {self.path} (UUID: {self.uuid})")
        self.notifying = False
        self.PropertiesChanged('org.bluez.GattCharacteristic1', {'Notifying': dbus.Boolean(False)}, [])

    @dbus.service.method('org.bluez.GattCharacteristic1', in_signature='aya{sv}', out_signature='')
    def WriteValue(self, value, options):
        data = [int(b) for b in value]
        print(f"[{strftime('%H:%M:%S')}] [Characteristic] WriteValue received {len(data)} bytes: {data}")
        
        # If this is the TX characteristic and we have a paired RX partner, echo it back
        if self.rx_partner and self.rx_partner.notifying:
            def echo():
                sleep(0.05)
                print(f"[{strftime('%H:%M:%S')}] [Characteristic] Echoing bytes back to RX path {self.rx_partner.path}")
                self.rx_partner.value = value
                self.rx_partner.PropertiesChanged('org.bluez.GattCharacteristic1', {
                    'Value': dbus.Array(value, signature='y')
                }, [])
            threading.Thread(target=echo, daemon=True).start()

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='ss', out_signature='v')
    def Get(self, interface, prop):
        if interface == 'org.bluez.GattCharacteristic1':
            if prop == 'UUID':
                return dbus.String(self.uuid)
            elif prop == 'Service':
                return dbus.ObjectPath(self.service_path)
            elif prop == 'Value':
                return dbus.Array(self.value, signature='y')
            elif prop == 'Notifying':
                return dbus.Boolean(self.notifying)
        raise dbus.exceptions.DBusException('org.freedesktop.DBus.Error.InvalidArgs')

    @dbus.service.method('org.freedesktop.DBus.Properties', in_signature='s', out_signature='a{sv}')
    def GetAll(self, interface):
        if interface == 'org.bluez.GattCharacteristic1':
            return {
                'UUID': dbus.String(self.uuid),
                'Service': dbus.ObjectPath(self.service_path),
                'Value': dbus.Array(self.value, signature='y'),
                'Notifying': dbus.Boolean(self.notifying)
            }
        return {}

    @dbus.service.signal('org.freedesktop.DBus.Properties', signature='sa{sv}as')
    def PropertiesChanged(self, interface, changed, invalidated):
        pass


class ObjectManager(dbus.service.Object):
    def __init__(self, bus, path, objects_to_manage):
        super().__init__(bus, path)
        self.objects_to_manage = objects_to_manage

    @dbus.service.method('org.freedesktop.DBus.ObjectManager', in_signature='', out_signature='a{oa{sa{sv}}}')
    def GetManagedObjects(self):
        result = {}
        for obj in self.objects_to_manage:
            result[obj.path] = {}
            if isinstance(obj, DeviceObject):
                result[obj.path]['org.bluez.Device1'] = obj.GetAll('org.bluez.Device1')
            elif isinstance(obj, GattServiceObject):
                result[obj.path]['org.bluez.GattService1'] = obj.GetAll('org.bluez.GattService1')
            elif isinstance(obj, GattCharacteristicObject):
                result[obj.path]['org.bluez.GattCharacteristic1'] = obj.GetAll('org.bluez.GattCharacteristic1')
        return result


def main() -> bool:
    '''
        Run D-Bus mock server for BlueZ.

        :return: True if all OK, False otherwise.
        :exceptions: None.
    '''
    parser = argparse.ArgumentParser(description="BlueZ BLE D-Bus Mock Server for restatdesk")
    parser.add_argument("--address", default=DEFAULT_MAC, help=f"MAC address to mock (default: {DEFAULT_MAC})")
    parser.add_argument("--service", default=DEFAULT_SERVICE_UUID, help=f"GATT Service UUID (default: {DEFAULT_SERVICE_UUID})")
    parser.add_argument("--rx", default=DEFAULT_RX_UUID, help=f"RX Characteristic UUID (default: {DEFAULT_RX_UUID})")
    parser.add_argument("--tx", default=DEFAULT_TX_UUID, help=f"TX Characteristic UUID (default: {DEFAULT_TX_UUID})")
    parser.add_argument("--session", action="store_true", help="Use D-Bus Session Bus instead of System Bus")
    args = parser.parse_args()

    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    
    if args.session:
        print("Connecting to D-Bus Session Bus...")
        bus = dbus.SessionBus()
    else:
        print("Connecting to D-Bus System Bus...")
        try:
            bus = dbus.SystemBus()
        except dbus.exceptions.DBusException as e:
            print(f"Error: Could not connect to System Bus: {e}")
            print("Please ensure dbus is running, or run the script as root / with sudo.")
            return False

    try:
        bus_name = dbus.service.BusName('org.bluez', bus)
    except dbus.exceptions.DBusException as e:
        print(f"Error: Could not acquire service name 'org.bluez': {e}")
        if not args.session:
            print("To acquire name on System Bus, you must run this script with 'sudo':")
            print(f"  sudo python3 {argv[0]}")
        return False

    # Standard path naming matching BlueZ adapter hierarchy
    dev_path = f"/org/bluez/hci0/dev_{args.address.replace(':', '_')}"
    service_path = f"{dev_path}/service0001"
    rx_char_path = f"{service_path}/char0002"
    tx_char_path = f"{service_path}/char0003"

    print("Initializing mock objects...")
    dev_obj = DeviceObject(bus, dev_path, args.address)
    srv_obj = GattServiceObject(bus, service_path, args.service, dev_path)
    rx_obj = GattCharacteristicObject(bus, rx_char_path, args.rx, service_path, is_rx=True)
    tx_obj = GattCharacteristicObject(bus, tx_char_path, args.tx, service_path, is_rx=False)

    # Pair them for loopback echo behavior
    tx_obj.rx_partner = rx_obj

    objects = [dev_obj, srv_obj, rx_obj, tx_obj]
    obj_manager = ObjectManager(bus, '/', objects)

    print(f"\nBLE D-Bus Mock Server is running successfully!")
    print(f"==================================================")
    print(f"Address:            {args.address}")
    print(f"Service UUID:       {args.service}")
    print(f"RX Characteristic:  {args.rx} ({rx_char_path})")
    print(f"TX Characteristic:  {args.tx} ({tx_char_path})")
    print(f"==================================================")
    print("Press any key to exit...")

    old_settings = tcgetattr(stdin)
    try:
        setcbreak(stdin.fileno())
        context = GLib.MainContext.default()

        while True:
            # Process GLib pending events (needed for dbus callbacks)
            context.iteration(False)

            # Check if any key is pressed to exit
            if select([stdin], [], [], 0) == ([stdin], [], []):
                stdin.read(1)
                print("\nExit key pressed.")
                break

            sleep(0.01)

    except KeyboardInterrupt:
        print("\nInterrupted by user.")

    finally:
        tcsetattr(stdin, TCSADRAIN, old_settings)

    return True


if __name__ == "__main__":
    sys_exit(0 if main() else 1)
