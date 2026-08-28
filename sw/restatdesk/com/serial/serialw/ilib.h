////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// ilib.h
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

#include <string>
#include <vector>
#include <cstdint>

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @namespace Electux::App::Com
/// @brief Namespace for application communication components
namespace Electux::App::Com
{
	enum class BaudRate : uint32_t
	{
		BAUD_INVALID = 0,
		BAUD_110,
		BAUD_300,
		BAUD_600,
		BAUD_1200,
		BAUD_2400,
		BAUD_4800,
		BAUD_9600,
		BAUD_19200,
		BAUD_38400,
		BAUD_57600,
		BAUD_115200,
		BAUD_230400
	};

	enum class CharacterSize : uint8_t
	{
		CHAR_SIZE_INVALID = 0,
		CHAR_SIZE_5,
		CHAR_SIZE_6,
		CHAR_SIZE_7,
		CHAR_SIZE_8
	};

	enum class Parity : uint8_t
	{
		PARITY_INVALID = 0,
		PARITY_NONE,
		PARITY_ODD,
		PARITY_EVEN
	};

	enum class StopBits : uint8_t
	{
		STOP_BITS_INVALID = 0,
		STOP_BITS_1,
		STOP_BITS_2
	};

	enum class FlowControl : uint8_t
	{
		FLOW_CONTROL_INVALID = 0,
		FLOW_CONTROL_NONE,
		FLOW_CONTROL_SOFTWARE,
		FLOW_CONTROL_HARDWARE
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class ILibSerialPort
	/// @brief Interface wrapper around LibSerial::SerialPort for testability.
	///
	/// This interface abstracts the LibSerial::SerialPort class, enabling dependency injection and
	/// mocking for unit testing. It provides methods to configure and interact with a serial port.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class ILibSerialPort
	{
	public:
		virtual ~ILibSerialPort() = default;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Opens the serial port device.
		/// @param device The path to the serial port device (e.g., "/dev/ttyS0").
		/// @throws std::runtime_error if the device cannot be opened.
		/// Implementation should call the underlying LibSerial method to open the port and handle
		/// any exceptions that may arise during the process.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Open(const std::string& device) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Closes the serial port device.
		/// Ensures that the port is properly closed and resources are released.
		/// Implementation should call the underlying LibSerial method to close the port and handle
		/// any exceptions that may arise during the process.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Close() = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Checks if the serial port is currently open.
		/// @return True if the port is open, false otherwise.
		/// Implementation should call the underlying LibSerial method to check the port status and
		/// return the appropriate boolean value.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual bool IsOpen() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads data from the serial port.
		/// @param data A vector to store the received bytes.
		/// @param len The number of bytes to read.
		/// @throws std::runtime_error if the port is not open or a read error occurs.
		/// Implementation should call the underlying LibSerial method to read data.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Read(std::vector<uint8_t>& data, size_t len) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Writes data to the serial port.
		/// @param data A vector containing the bytes to transmit.
		/// @throws std::runtime_error if the port is not open or a write error occurs.
		/// Implementation should call the underlying LibSerial method to write data.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Write(const std::vector<uint8_t>& data) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the baud rate for the serial port.
		/// @param baudRate The desired baud rate (e.g., BaudRate::BAUD_9600).
		/// Implementation should call the underlying LibSerial method to apply baud rate settings.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetBaudRate(BaudRate baudRate) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the character size for the serial port.
		/// @param characterSize The desired character size (e.g., CharacterSize::CHAR_SIZE_8).
		/// Implementation should call the underlying LibSerial method to apply the character size.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetCharacterSize(CharacterSize characterSize) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the parity mode for the serial port.
		/// @param parity The desired parity mode (e.g., Parity::PARITY_NONE).
		/// Implementation should call the underlying LibSerial method to apply the parity setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetParity(Parity parity) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the number of stop bits for the serial port.
		/// @param stopBits The desired number of stop bits (e.g., StopBits::STOP_BITS_1).
		/// Implementation should call the underlying LibSerial method to apply the stop bits setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetStopBits(StopBits stopBits) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the flow control mode for the serial port.
		/// @param flowControl The desired flow control mode (e.g., FlowControl::FLOW_CONTROL_NONE).
		/// Implementation should call the underlying LibSerial method to apply the flow control setting.
		////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void SetFlowControl(FlowControl flowControl) = 0;
	};
} // namespace Electux::App::Com
