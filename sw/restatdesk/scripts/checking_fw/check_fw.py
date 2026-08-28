# -*- coding: UTF-8 -*-

'''
Module
    check_fw.py
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
    A simple script for testing firmware on restat device.
'''

from __future__ import annotations

from serial import Serial
from sys import exit as sys_exit
from time import sleep

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/restat'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/restat/blob/dev/LICENSE'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


DEVICE = '/dev/ttyACM0'
BAUD = 115200

def test_command(ser, cmd_str, expected_part):
    full_cmd = f"<{cmd_str}>".encode('utf-8')
    print(f"  Sending: {cmd_str}")
    ser.write(full_cmd)
    
    sleep(0.15)
    waiting = ser.in_waiting
    if waiting > 0:
        raw_resp = ser.read(waiting)
        resp_str = raw_resp.decode('utf-8', errors='replace').strip()
        print(f"  Received: {resp_str}")
        if expected_part in resp_str:
            print("  [OK] Response matched.")
            return True
        else:
            print(f"  [ERROR] Response did not contain expected: '{expected_part}'")
            return False
    else:
        print("  [ERROR] No response received!")
        return False

def main() -> bool:
    try:
        serial_port = Serial(DEVICE, BAUD, timeout=1.0)
        serial_port.reset_input_buffer()
        print(f"Successfully connected to {DEVICE}")
    except Exception as e:
        print(f"Failed to open {DEVICE}: {e}")
        print("Make sure the restat hardware is connected and desktop application is closed.")
        return False

    print("\n--- Starting firmware test for all channels and modes ---")
    
    for ch in range(1, 9):
        print(f"\n================ TESTING CHANNEL {ch} ================")
        
        # 1. Toggle Mode Test
        print("\n[Mode 1: Toggle]")
        test_command(serial_port, f"rs#ch#{ch}#on#end", f"channel {ch} on")
        sleep(0.2)
        test_command(serial_port, f"rs#ch#{ch}#off#end", f"channel {ch} off")
        
        # 2. Timer Mode Test
        print("\n[Mode 2: Timer]")
        test_command(serial_port, f"rs#ch#{ch}#tmr#5#end", f"timer started")
        sleep(0.2)
        test_command(serial_port, f"rs#ch#{ch}#off#end", f"channel {ch} off")
        
        # 3. Pulse Mode Test
        print("\n[Mode 3: Pulse]")
        test_command(serial_port, f"rs#ch#{ch}#pulse#2000#end", f"pulse started")
        sleep(0.2)
        # Turn off mid-pulse
        test_command(serial_port, f"rs#ch#{ch}#off#end", f"channel {ch} off")
        
        # 4. Blink Mode Test
        print("\n[Mode 4: Blink]")
        test_command(serial_port, f"rs#ch#{ch}#blink#500#500#5#end", f"blink started")
        sleep(0.2)
        # Turn off mid-blink
        test_command(serial_port, f"rs#ch#{ch}#off#end", f"channel {ch} off")

    serial_port.close()
    print("\nTest completed.")
    return True


if __name__ == '__main__':
    sys_exit(0 if main() else 1)
