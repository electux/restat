////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// serial_lib_wrapper.cc
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

#include <cerrno>
#include <com/serial/serialw/SerialPortConstants.h>
#include <com/serial/serialw/serial_lib_wrapper.h>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace Electux::App::Com;

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Constructs a LibSerialPortWrapper object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
LibSerialPortWrapper::LibSerialPortWrapper() : m_fd(-1) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Destroys the LibSerialPortWrapper object.
////////////////////////////////////////////////////////////////////////////////////////////////////////
LibSerialPortWrapper::~LibSerialPortWrapper() { Close(); }

void LibSerialPortWrapper::checkOpen() const {
    if (m_fd < 0) {
        throw LibSerial::NotOpen("Port not open.");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Opens the serial port with the specified device.
/// @param device The name of the device to open.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Open(const std::string &device) {
    Close();
    m_device = device;
    m_fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_CLOEXEC);
    if (m_fd < 0) {
        throw std::runtime_error(
            "Failed to open device: " + device + " (" +
            std::string(std::strerror(errno)) + ")"
        );
    }

    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));
    if (tcgetattr(m_fd, &tty) != 0) {
        int err = errno;
        close(m_fd);
        m_fd = -1;
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(err))
        );
    }

    // Configure as raw serial port (binary mode)
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= ~OPOST;
    tty.c_iflag &=
        ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR |
          IGNCR | ICRNL);

    // Blocking read settings: return when at least 1 byte is available
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        int err = errno;
        close(m_fd);
        m_fd = -1;
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(err))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Closes the serial port.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Close() {
    if (m_fd >= 0) {
        close(m_fd);
        m_fd = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the serial port is open.
/// @return True if the serial port is open, false otherwise.
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LibSerialPortWrapper::IsOpen() const {
    if (m_fd < 0) {
        return false;
    }

    if (!m_device.empty() && !std::filesystem::exists(m_device)) {
        return false;
    }

    struct pollfd pfd;
    pfd.fd = m_fd;
    pfd.events = POLLIN | POLLERR | POLLHUP;
    pfd.revents = 0;
    int ret = poll(&pfd, 1, 0);

    if (ret > 0 && (pfd.revents & (POLLERR | POLLHUP | POLLNVAL))) {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Reads data from the serial port.
/// @param data A vector to store the read data.
/// @param len The number of bytes to read.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Read(std::vector<uint8_t> &data, size_t len) {
    checkOpen();
    data.clear();
    data.resize(len);
    size_t total_read = 0;

    while (total_read < len) {
        if (!m_device.empty() && !std::filesystem::exists(m_device)) {
            throw std::runtime_error("Device disconnected (file deleted).");
        }

        struct pollfd pfd;
        pfd.fd = m_fd;
        pfd.events = POLLIN | POLLERR | POLLHUP;
        pfd.revents = 0;

        int ret = poll(&pfd, 1, 500); // 500ms timeout
        if (ret == 0) {
            throw LibSerial::ReadTimeout("Timeout waiting for data.");
        } else if (ret < 0) {
            if (errno == EINTR)
                continue;
            throw std::runtime_error(
                "Read error (poll failed): " + std::string(std::strerror(errno))
            );
        }

        if (pfd.revents & (POLLERR | POLLHUP | POLLNVAL)) {
            throw std::runtime_error("Connection lost (device disconnected).");
        }

        ssize_t n = read(m_fd, data.data() + total_read, len - total_read);
        if (n < 0) {
            if (errno == EAGAIN || errno == EINTR)
                continue;
            throw std::runtime_error(
                "Read error: " + std::string(std::strerror(errno))
            );
        } else if (n == 0) {
            throw std::runtime_error("Connection lost (EOF).");
        }
        total_read += static_cast<size_t>(n);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Writes data to the serial port.
/// @param data The data to write.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::Write(const std::vector<uint8_t> &data) {
    checkOpen();
    size_t total_written = 0;

    while (total_written < data.size()) {
        ssize_t n = write(
            m_fd, data.data() + total_written, data.size() - total_written
        );

        if (n < 0) {
            if (errno == EINTR)
                continue;

            throw std::runtime_error(
                "Write error: " + std::string(std::strerror(errno))
            );
        }

        total_written += static_cast<size_t>(n);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the baud rate of the serial port.
/// @param baudRate The baud rate to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetBaudRate(BaudRate baudRate) {
    checkOpen();
    speed_t speed = B9600;
    switch (baudRate) {
    case BaudRate::BAUD_110:
        speed = B110;
        break;
    case BaudRate::BAUD_300:
        speed = B300;
        break;
    case BaudRate::BAUD_600:
        speed = B600;
        break;
    case BaudRate::BAUD_1200:
        speed = B1200;
        break;
    case BaudRate::BAUD_2400:
        speed = B2400;
        break;
    case BaudRate::BAUD_4800:
        speed = B4800;
        break;
    case BaudRate::BAUD_9600:
        speed = B9600;
        break;
    case BaudRate::BAUD_19200:
        speed = B19200;
        break;
    case BaudRate::BAUD_38400:
        speed = B38400;
        break;
    case BaudRate::BAUD_57600:
        speed = B57600;
        break;
    case BaudRate::BAUD_115200:
        speed = B115200;
        break;
    case BaudRate::BAUD_230400:
        speed = B230400;
        break;
    default:
        throw std::invalid_argument("Invalid baud rate.");
    }

    struct termios tty;
    if (tcgetattr(m_fd, &tty) != 0) {
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(errno))
        );
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);
    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(errno))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the character size of the serial port.
/// @param characterSize The character size to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetCharacterSize(CharacterSize characterSize) {
    checkOpen();
    tcflag_t size = CS8;

    switch (characterSize) {
    case CharacterSize::CHAR_SIZE_5:
        size = CS5;
        break;
    case CharacterSize::CHAR_SIZE_6:
        size = CS6;
        break;
    case CharacterSize::CHAR_SIZE_7:
        size = CS7;
        break;
    case CharacterSize::CHAR_SIZE_8:
        size = CS8;
        break;
    default:
        throw std::invalid_argument("Invalid character size.");
    }

    struct termios tty;
    if (tcgetattr(m_fd, &tty) != 0) {
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(errno))
        );
    }
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= size;
    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(errno))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the parity of the serial port.
/// @param parity The parity to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetParity(Parity parity) {
    checkOpen();
    struct termios tty;
    if (tcgetattr(m_fd, &tty) != 0) {
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(errno))
        );
    }

    switch (parity) {
    case Parity::PARITY_NONE:
        tty.c_cflag &= ~PARENB;
        break;
    case Parity::PARITY_ODD:
        tty.c_cflag |= PARENB;
        tty.c_cflag |= PARODD;
        break;
    case Parity::PARITY_EVEN:
        tty.c_cflag |= PARENB;
        tty.c_cflag &= ~PARODD;
        break;
    default:
        throw std::invalid_argument("Invalid parity.");
    }

    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(errno))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the stop bits of the serial port.
/// @param stopBits The stop bits to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetStopBits(StopBits stopBits) {
    checkOpen();
    struct termios tty;

    if (tcgetattr(m_fd, &tty) != 0) {
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(errno))
        );
    }

    switch (stopBits) {
    case StopBits::STOP_BITS_1:
        tty.c_cflag &= ~CSTOPB;
        break;
    case StopBits::STOP_BITS_2:
        tty.c_cflag |= CSTOPB;
        break;
    default:
        throw std::invalid_argument("Invalid stop bits.");
    }

    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(errno))
        );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Sets the flow control of the serial port.
/// @param flowControl The flow control to set.
////////////////////////////////////////////////////////////////////////////////////////////////////////
void LibSerialPortWrapper::SetFlowControl(FlowControl flowControl) {
    checkOpen();
    struct termios tty;

    if (tcgetattr(m_fd, &tty) != 0) {
        throw std::runtime_error(
            "tcgetattr failed: " + std::string(std::strerror(errno))
        );
    }

    switch (flowControl) {
    case FlowControl::FLOW_CONTROL_NONE:
        tty.c_cflag &= ~CRTSCTS;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    case FlowControl::FLOW_CONTROL_SOFTWARE:
        tty.c_cflag &= ~CRTSCTS;
        tty.c_iflag |= (IXON | IXOFF | IXANY);
        break;
    case FlowControl::FLOW_CONTROL_HARDWARE:
        tty.c_cflag |= CRTSCTS;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        break;
    default:
        throw std::invalid_argument("Invalid flow control.");
    }

    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        throw std::runtime_error(
            "tcsetattr failed: " + std::string(std::strerror(errno))
        );
    }
}
