////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_com.cc
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

#include <com/serial/serial_com.h>
#include <com/serial/serialw/serial_lib_wrapper.h>
#include <com/serial/serialw/SerialPortConstants.h>
#include <iostream>

using namespace Electux::App::Com;

namespace {
    constexpr std::string_view cConstructorMsg{"SerialCom constructor called."};
    constexpr std::string_view cDestructorMsg{"SerialCom destructor called."};
    constexpr std::string_view cCloseErrorMsg{"Close error: Serial port was not closed properly."};
    constexpr std::string_view cExceptionCloseErrorMsg{"Exception in destructor during close(): "};
    constexpr std::string_view cUnknownExceptionMsg{"Unknown exception in SerialCom destructor."};
    constexpr std::string_view cOpenEmptyDeviceError{"Open error: Device path is empty!"};
    constexpr std::string_view cOpenSuccessMsg{"Serial port opened successfully."};
    constexpr std::string_view cOpenExceptionError{"Open error: "};
    constexpr std::string_view cCloseSuccessMsg{"Serial port closed successfully."};
    constexpr std::string_view cReadError{"Read error: Serial port closed."};
    constexpr std::string_view cWriteError{"Write error: Serial port closed."};
    constexpr std::string_view cSetupNotOpenError{"Setup error: Serial port not open."};
    constexpr std::string_view cSetupEmptyDeviceError{"Setup error: Device path is empty!"};
    constexpr std::string_view cSetupExceptionError{"Setup error: "};
} // namespace

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructs a SerialCom object with the given serial port adapter.
/// @param port A unique pointer to an ILibSerialPort implementation.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SerialCom::SerialCom(bool verbose)
    : m_serialPort(std::make_unique<LibSerialPortWrapper>()), m_verbose(verbose) {
    if (m_verbose) {
        std::cout << cConstructorMsg << std::endl;
    }
}

SerialCom::SerialCom(std::unique_ptr<ILibSerialPort> port, bool verbose)
    : m_serialPort(
          port ? std::move(port) : std::make_unique<LibSerialPortWrapper>()
      ),
      m_verbose(verbose) {
    if (m_verbose) {
        std::cout << cConstructorMsg << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destructor for the SerialCom class. Ensures the serial port is
/// closed.
////////////////////////////////////////////////////////////////////////////////////////////////////////
SerialCom::~SerialCom() noexcept {
    try {
        if (isOpen()) {
            if (!close()) {
                std::cerr << cCloseErrorMsg
                          << std::endl;
            }
        }
    } catch (const std::exception &e) {
        // Log the error but DO NOT rethrow
        std::cerr << cExceptionCloseErrorMsg << e.what()
                  << std::endl;
    } catch (...) {
        std::cerr << cUnknownExceptionMsg << std::endl;
    }

    if (m_verbose) {
        std::cout << cDestructorMsg << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the serial port.
/// @return True if the port was successfully opened, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::open() {
    if (m_device.empty()) {
        std::cerr << cOpenEmptyDeviceError << std::endl;
        return false;
    }

    if (!isOpen()) {
        try {
            m_serialPort->Open(m_device);
            if (m_verbose) {
                std::cout << cOpenSuccessMsg << std::endl;
            }
            return true;
        } catch (const std::exception &e) {
            std::cerr << cOpenExceptionError << e.what() << std::endl;
        } catch (...) {
            std::cerr << cOpenExceptionError << "Unknown error during open." << std::endl;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Closes the serial port.
/// @return True if the port was successfully closed, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::close() {
    if (isOpen()) {
        try {
            m_serialPort->Close();
        } catch (...) {
        }
        if (m_verbose) {
            std::cout << cCloseSuccessMsg << std::endl;
        }
        return true;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the serial port is open.
/// @return True if the port is open, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::isOpen() const {
    bool open = m_serialPort->IsOpen();
    // std::cout << "Serial port is " << (open ? "open." : "closed.") <<
    // std::endl;
    return open;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from the serial port.
/// @param data A vector to store the read data.
/// @param len The number of bytes to read.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::read(std::vector<uint8_t> &data, size_t len) {
    if (!isOpen()) {
        std::cerr << cReadError << std::endl;
        return;
    }

    try {
        m_serialPort->Read(data, len);
    } catch (const LibSerial::ReadTimeout &) {
        // Normal timeout when no data is received, do not close the port.
    } catch (const std::exception &e) {
        if (m_verbose) {
            std::cerr << cReadError << ": " << e.what() << std::endl;
        }
        try {
            m_serialPort->Close();
        } catch (...) {
        }
    } catch (...) {
        if (m_verbose) {
            std::cerr << cReadError << ": Unknown exception occurred (possibly I/O error)." << std::endl;
        }
        try {
            m_serialPort->Close();
        } catch (...) {
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Writes data to the serial port.
/// @param data A vector containing the data to write.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::write(const std::vector<uint8_t> &data) {
    if (!isOpen()) {
        std::cerr << cWriteError << std::endl;
        return;
    }

    try {
        m_serialPort->Write(data);
    } catch (const std::exception &e) {
        std::cerr << cWriteError << ": " << e.what() << std::endl;
        try {
            m_serialPort->Close();
        } catch (...) {
        }
    } catch (...) {
        std::cerr << cWriteError << ": Unknown exception occurred during write." << std::endl;
        try {
            m_serialPort->Close();
        } catch (...) {
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Configures the serial port device file path.
/// @param device Path to the serial port device.
////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setDevice(const std::string &device) { m_device = device; }

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the baud rate for the serial port.
/// @param baudRate The desired baud rate.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setBaudRate(BaudRate baudRate) {
    try {
        m_serialPort->SetBaudRate(baudRate);
    } catch (...) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the character size for the serial port.
/// @param characterSize The desired character size.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setCharacterSize(CharacterSize characterSize) {
    try {
        m_serialPort->SetCharacterSize(characterSize);
    } catch (...) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the parity mode for the serial port.
/// @param parity The desired parity mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setParity(Parity parity) {
    try {
        m_serialPort->SetParity(parity);
    } catch (...) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the number of stop bits for the serial port.
/// @param stopBits The desired number of stop bits.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setStopBits(StopBits stopBits) {
    try {
        m_serialPort->SetStopBits(stopBits);
    } catch (...) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the flow control mode for the serial port.
/// @param flowControl The desired flow control mode.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void SerialCom::setFlowControl(FlowControl flowControl) {
    try {
        m_serialPort->SetFlowControl(flowControl);
    } catch (...) {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Configures the serial port with specific parameters.
/// @param params Reference to SerialParams structure (configuration).
/// @return True if setup was successful, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SerialCom::setup(const SerialParams &params) {
    if (!isOpen()) {
        std::cerr << cSetupNotOpenError << std::endl;
        return false;
    }

    if (params.device.empty()) {
        std::cerr << cSetupEmptyDeviceError << std::endl;
        return false;
    }

    try {
        setBaudRate(params.baud);
        setCharacterSize(params.data);
        setParity(params.parity);
        setStopBits(params.stop);
        setFlowControl(params.flow);
        m_device = params.device;
        return true;

    } catch (const std::exception &e) {
        std::cerr << cSetupExceptionError << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << cSetupExceptionError << "Unknown error during setup." << std::endl;
        return false;
    }
}
