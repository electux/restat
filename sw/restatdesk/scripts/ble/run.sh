#!/usr/bin/env bash
#
# @brief   Run BlueZ BLE mock server for testing
# @version ver.2.0
# @date    Sat Aug 22 14:06:00 PM CEST 2026
# @company None, free software to use 2026
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

USE_SYSTEM=0
for arg in "$@"; do
    if [ "$arg" == "--system" ]; then
        USE_SYSTEM=1
    fi
done

if [ "$USE_SYSTEM" -eq 1 ]; then
    # System Bus Mode (Requires root/sudo)
    if [ "$EUID" -ne 0 ]; then
        echo "Please run as root (using sudo) for System Bus mode:"
        echo "  sudo $0 --system"
        exit 1
    fi

    # Determine if the bluetooth service was originally active
    WAS_ACTIVE=0
    if systemctl is-active --quiet bluetooth; then
        WAS_ACTIVE=1
        echo "Stopping system bluetooth service..."
        systemctl stop bluetooth
    fi

    # Always kill any remaining bluetoothd processes to ensure the D-Bus name is freed
    if killall -0 bluetoothd 2>/dev/null; then
        echo "Killing remaining bluetoothd processes..."
        killall -9 bluetoothd 2>/dev/null
    fi

    # Always mask to prevent D-Bus activation while the emulator is running
    systemctl mask bluetooth

    # Function to clean up and restore bluetooth service on exit
    cleanup() {
        echo ""
        echo "Unmasking bluetooth service..."
        systemctl unmask bluetooth
        if [ "$WAS_ACTIVE" -eq 1 ]; then
            echo "Restoring system bluetooth service..."
            systemctl start bluetooth
        fi
        exit 0
    }

    # Trap SIGINT, SIGTERM, and EXIT to run cleanup
    trap cleanup INT TERM EXIT

    # Run the python BLE mock server on System Bus
    python3 -u run-ble.py --address "00:11:22:33:44:55"
else
    # Session Bus Mode (Default, No sudo needed!)
    echo "Running BLE Mock Server on Session Bus (Recommended for testing)..."
    python3 -u run-ble.py --session --address "00:11:22:33:44:55"
fi
