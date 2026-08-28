/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_gpio.h
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * restat-base is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * restat-base is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes a GPIO pin as input or output
///
/// @param pin [in] GPIO pin number to initialize
/// @param is_output [in] True to configure as output, false for input
void io_gpio_init(uint32_t pin, bool is_output);

////////////////////////////////////////////////////////////////////////////
/// @brief Drives a GPIO pin to a high or low level
///
/// @param pin [in] GPIO pin number to write
/// @param value [in] True to set high, false to set low
void io_gpio_write(uint32_t pin, bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Reads the current state of a GPIO pin
///
/// @param pin [in] GPIO pin number to read
/// @return True if the pin is high, false if low
bool io_gpio_read(uint32_t pin);

#ifdef __cplusplus
}
#endif
