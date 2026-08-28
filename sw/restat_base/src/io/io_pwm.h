/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_pwm.h
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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes PWM on a specific pin and PWM channel
///
/// @param pin [in] GPIO pin to initialize for PWM
/// @param channel [in] PWM channel to use
void io_pwm_init(uint32_t pin, uint32_t channel);

////////////////////////////////////////////////////////////////////////////
/// @brief Writes PWM duty cycle to a specific pin and PWM channel
///
/// @param pin [in] GPIO pin with PWM enabled
/// @param channel [in] PWM channel to write
/// @param duty_percent [in] Duty cycle as percentage (0-100)
void io_pwm_write(uint32_t pin, uint32_t channel, uint16_t duty_percent);

#ifdef __cplusplus
}
#endif
