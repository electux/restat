# -*- coding: UTF-8 -*-

'''
Module
    run-tcp-server.py
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
    A simple script for demonstrating TCP/IP socket server communication.
'''

from __future__ import annotations

from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
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
        Listen on TCP port 5000 for incoming data and print it to the console.

        :return: True if all OK, False otherwise.
        :exceptions: None.
    '''
    HOST = '0.0.0.0'
    PORT = 5000

    try:
        server_sock = socket(AF_INET, SOCK_STREAM)
        server_sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        server_sock.bind((HOST, PORT))
        server_sock.listen()
        server_sock.setblocking(False)

    except OSError as e:
        print(f"Error starting TCP server: {e}")
        return False

    print(f"Starting TCP server on {HOST}:{PORT}...")
    print("Press any key to exit...")

    old_settings = tcgetattr(stdin)
    try:
        setcbreak(stdin.fileno())

        while True:
            # Wait for stdin keypress or incoming TCP connection
            readable, _, _ = select([stdin, server_sock], [], [], 0.1)

            if stdin in readable:
                stdin.read(1)
                print("\nExit key pressed.")
                break

            if server_sock in readable:
                conn, addr = server_sock.accept()
                conn.setblocking(False)
                print(f"\n[{strftime('%H:%M:%S')}] Client connected from: {addr}")

                with conn:
                    client_disconnected = False
                    while not client_disconnected:
                        # Wait for stdin keypress or client data
                        r, _, _ = select([stdin, conn], [], [], 0.1)

                        if stdin in r:
                            stdin.read(1)
                            print("\nExit key pressed.")
                            return True

                        if conn in r:
                            data = conn.recv(1024)
                            if not data:
                                print(f"[{strftime('%H:%M:%S')}] Client closed connection.")
                                client_disconnected = True
                            else:
                                print(f"[{strftime('%H:%M:%S')}] Received {len(data)} bytes:")
                                print(f"  Hex: {data.hex(' ')}")
                                print(f"  Raw: {data.decode('utf-8', errors='replace')}")

            sleep(0.01)

    except KeyboardInterrupt:
        print("\nInterrupted by user.")

    finally:
        tcsetattr(stdin, TCSADRAIN, old_settings)
        server_sock.close()

    return True


if __name__ == "__main__":
    sys_exit(0 if main() else 1)
