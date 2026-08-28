# -*- coding: UTF-8 -*-

'''
Module
    run-serial-port.py
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
    A simple script for demonstrating UART communication.
'''

from __future__ import annotations

from serial import Serial
from select import select
from sys import stdin, exit as sys_exit
from termios import tcgetattr, tcsetattr, TCSADRAIN
from tty import setcbreak
from time import sleep, strftime

__author__ = 'Vladimir Roncevic'
__copyright__ = '(C) 2026, https://vroncevic.github.io/restat'
__credits__ = ['Vladimir Roncevic', 'Python Software Foundation']
__license__ = 'https://github.com/vroncevic/restat/blob/dev/LICENSE'
__version__ = '1.0.0'
__maintainer__ = 'Vladimir Roncevic'
__email__ = 'elektron.ronca@gmail.com'
__status__ = 'Updated'


def main() -> bool:
    '''
        Listen on serial port /tmp/ttyV1 for incoming data and print it to the console.

        :return: True if all OK, False otherwise.
        :exceptions: None.
    '''
    try:
        serial_port = Serial('/tmp/ttyV1', 115200, timeout=0.1)

    except OSError as e:
        print(f"Error opening serial port: {e}")
        return False

    print("Listening on /tmp/ttyV1 (PTY slave)...")
    print("Parameters: 115200, 8N1...")
    print("Press any key to exit...")

    old_settings = tcgetattr(stdin)
    buffer = bytearray()

    try:
        setcbreak(stdin.fileno())

        while True:
            if select([stdin], [], [], 0) == ([stdin], [], []):
                stdin.read(1)
                print("\nExit key pressed.")
                break

            waiting = serial_port.in_waiting

            if waiting > 0:
                raw_data = serial_port.read(waiting)
                buffer.extend(raw_data)
                
                print(f"[{strftime('%H:%M:%S')}] Received {len(raw_data)} bytes: {raw_data.hex(' ')} ({raw_data})")

                while b"<" in buffer and b">" in buffer:
                    start = buffer.find(b"<")
                    end = buffer.find(b">", start)

                    if end == -1:
                        break

                    msg = bytes(buffer[start:end + 1])
                    del buffer[:end + 1]

                    print(f"  -> Parsed packet: {msg.decode('utf-8', errors='replace')}")

                    if msg == b"<rs#sys#id#end>":
                        response = b"<rs#sys#rs:333:2023:0#end>"
                        serial_port.write(response)
                        print(f"  <- Sent ID: {response}")

                    elif msg == b"<rs#sys#version#end>":
                        response = b"<rs#sys#restat v1.0.0#end>"
                        serial_port.write(response)
                        print(f"  <- Sent Version: {response}")

                    else:
                        serial_port.write(msg)

            sleep(0.01)

    except KeyboardInterrupt:
        print("\nInterrupted by user.")

    finally:
        tcsetattr(stdin, TCSADRAIN, old_settings)

    serial_port.close()

    return True


if __name__ == "__main__":
    sys_exit(0 if main() else 1)
