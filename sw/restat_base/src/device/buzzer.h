/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * buzzer.h
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
/// @brief Initializes PWM for the buzzer
///
/// @return True if initialization succeeded, false otherwise
bool buzzer_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Writes a duty cycle level to the buzzer PWM channel
///
/// @param value [in] PWM level value (0 to 100)
void buzzer_write(uint16_t value);

////////////////////////////////////////////////////////////////////////////
/// @brief Triggers a short startup notification beep
void buzzer_beep_start(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Triggers a short non-blocking notification beep for state changes
void buzzer_beep_changed(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Polling tick function to turn off buzzer non-blockingly
void buzzer_tick(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Triggers a longer shutdown/reset beep (blocking, pre-reset)
void buzzer_beep_stop(void);

#ifdef __cplusplus
}
#endif
