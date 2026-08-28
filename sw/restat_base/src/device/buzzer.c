/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * buzzer.c
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
#include <buzzer.h>
#include <io/io_pwm.h>
#include <pico/stdlib.h>

static const uint32_t BUZZER_PIN = 6;
static const uint32_t BUZZER_PWM_CHAN = 0; // PWM_CHAN_A

static const uint16_t BUZZER_BEEP_START_DUTY = 80;
static const uint32_t BUZZER_BEEP_START_MS = 100;

static const uint16_t BUZZER_BEEP_CHANGED_DUTY = 80;
static const uint32_t BUZZER_BEEP_CHANGED_MS = 50;

static const uint16_t BUZZER_BEEP_STOP_DUTY = 100;
static const uint32_t BUZZER_BEEP_STOP_MS = 300;

static const uint64_t US_TO_MS = 1000;

bool buzzer_init(void) {
  io_pwm_init(BUZZER_PIN, BUZZER_PWM_CHAN);
  io_pwm_write(BUZZER_PIN, BUZZER_PWM_CHAN, 0);
  return true;
}

void buzzer_write(uint16_t value) {
  io_pwm_write(BUZZER_PIN, BUZZER_PWM_CHAN, value);
}

void buzzer_beep_start(void) {
  buzzer_write(BUZZER_BEEP_START_DUTY);
  sleep_ms(BUZZER_BEEP_START_MS);
  buzzer_write(0);
}

static uint64_t buzzer_off_time = 0;

void buzzer_beep_changed(void) {
  buzzer_write(BUZZER_BEEP_CHANGED_DUTY);
  buzzer_off_time = time_us_64() / US_TO_MS + BUZZER_BEEP_CHANGED_MS;
}

void buzzer_tick(void) {
  if (buzzer_off_time > 0) {
    if ((time_us_64() / US_TO_MS) >= buzzer_off_time) {
      buzzer_write(0);
      buzzer_off_time = 0;
    }
  }
}

void buzzer_beep_stop(void) {
  buzzer_write(BUZZER_BEEP_STOP_DUTY);
  sleep_ms(BUZZER_BEEP_STOP_MS);
  buzzer_write(0);
}
