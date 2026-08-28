/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * status_led.h
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
/// @brief Initializes PIO state machine for the WS2812 status LED
///
/// @return True if initialization succeeded, false otherwise
bool status_led_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Writes red, green, and blue values to the WS2812 status LED
///
/// @param red [in] Red component intensity (0 to 255)
/// @param green [in] Green component intensity (0 to 255)
/// @param blue [in] Blue component intensity (0 to 255)
void status_led_write(uint8_t red, uint8_t green, uint8_t blue);

#ifdef __cplusplus
}
#endif
