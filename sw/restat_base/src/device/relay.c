/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * relay.c
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
#include <relay.h>
#include <buzzer.h>
#include <io/io_gpio.h>
#include <pico/stdlib.h>
#include <stdio.h>

static const uint32_t relay_pins[RELAY_NUM_CHANNELS] = {
    21, 20, 19, 18, 17, 16, 15, 14,
};

static const uint64_t US_TO_MS = 1000;
static const uint64_t MS_TO_SEC = 1000;

typedef struct {
  relay_mode_t mode;
  bool active;
  uint64_t start_time;
  uint64_t duration_ms;
  bool start_on;
} relay_state_internal_t;

static relay_state_internal_t relay_states[RELAY_NUM_CHANNELS];
static bool current_phys_state[RELAY_NUM_CHANNELS] = {false};

bool relay_init(void) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    io_gpio_init(relay_pins[i], true);
    io_gpio_write(relay_pins[i], true);
    current_phys_state[i] = false;
    
    relay_states[i].mode = RELAY_MODE_TOGGLE;
    relay_states[i].active = false;
    relay_states[i].start_time = 0;
    relay_states[i].duration_ms = 0;
    relay_states[i].start_on = false;
  }
  return true;
}

static void relay_set_phys(uint32_t channel, bool state) {
  if (channel < RELAY_NUM_CHANNELS) {
    if (current_phys_state[channel] != state) {
      current_phys_state[channel] = state;
      io_gpio_write(relay_pins[channel], !state);
      buzzer_beep_changed();
    }
  }
}

void relay_set(uint32_t channel, bool state) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].active = false;
    relay_states[channel].mode = RELAY_MODE_TOGGLE;
    relay_set_phys(channel, state);
  }
}

void relay_set_all(bool state) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    relay_set(i, state);
  }
}

void relay_start_timer(uint32_t channel, uint32_t duration_ms, bool start_on) {
  if (channel < RELAY_NUM_CHANNELS) {
    relay_states[channel].mode = RELAY_MODE_TIMER;
    relay_states[channel].active = true;
    relay_states[channel].start_time = time_us_64() / US_TO_MS;
    relay_states[channel].duration_ms = (uint64_t)duration_ms;
    relay_states[channel].start_on = start_on;
    relay_set_phys(channel, start_on);
  }
}

void relay_tick(void) {
  uint64_t now_ms = time_us_64() / US_TO_MS;
  for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
    if (!relay_states[i].active) {
      continue;
    }

    if (relay_states[i].mode == RELAY_MODE_TIMER) {
      if (now_ms - relay_states[i].start_time >= relay_states[i].duration_ms) {
        bool next_state = !relay_states[i].start_on;
        relay_set_phys(i, next_state);
        relay_states[i].active = false;
        relay_states[i].mode = RELAY_MODE_TOGGLE;
        printf("<rs#sys#channel %u %s#end>", i + 1, next_state ? "on" : "off");
        fflush(stdout);
      }
    }
  }
}

void relay_get_status(uint32_t channel, char *buf, uint32_t max_len) {
  if (channel >= RELAY_NUM_CHANNELS) {
    snprintf(buf, max_len, "invalid channel");
    return;
  }

  const char *phys_state = current_phys_state[channel] ? "ON" : "OFF";
  if (!relay_states[channel].active) {
    snprintf(buf, max_len, "Channel %u: %s (Toggle)", channel + 1, phys_state);
  } else {
    switch (relay_states[channel].mode) {
      case RELAY_MODE_TIMER: {
        uint64_t elapsed = time_us_64() / US_TO_MS - relay_states[channel].start_time;
        uint64_t remaining = (relay_states[channel].duration_ms > elapsed) ? 
                             (relay_states[channel].duration_ms - elapsed) : 0;
        snprintf(buf, max_len, "Channel %u: %s (Timer, rem: %llums)",
                 channel + 1, phys_state, remaining);
        break;
      }
      default:
        snprintf(buf, max_len, "Channel %u: %s", channel + 1, phys_state);
        break;
    }
  }
}
