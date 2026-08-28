/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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

#include <command/dispatcher.h>
#include <command/parser.h>
#include <device/buzzer.h>
#include <device/relay.h>
#include <device/status_led.h>
#include <device/persist.h>
#include <pico/stdlib.h>
#include <tusb.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

enum { RESTAT_REQ_LEN = 256 };
static const uint32_t USB_CONN_CHECK_MS = 100;

////////////////////////////////////////////////////////////////////////////
/// @brief Performs unified initialization of all hardware devices
/// @return true for success else false
static bool device_init(void) {
  if (!stdio_init_all()) {
    return false;
  }

  if (!relay_init()) {
    return false;
  }

  if (!status_led_init()) {
    return false;
  }

  if (!buzzer_init()) {
    return false;
  }

  buzzer_beep_start();

  return true;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point for restat-base
/// @return 0 for success exit else 1 for failed exit
int main() {
  ////////////////////////////////////////////////////////////////////////////
  /// Performs device initialization
  if (!device_init()) {
    return 1;
  }

  ////////////////////////////////////////////////////////////////////////////
  /// Waits for USB connection
  while (!tud_cdc_connected()) {
    sleep_ms(USB_CONN_CHECK_MS);
  }

  // Load and execute persisted plan if any
  char persisted_plan[PERSIST_MAX_LEN] = {0};
  if (persist_load_plan(persisted_plan, sizeof(persisted_plan))) {
    printf("<rs#sys#loading persisted plan: %s#end>\n", persisted_plan);
    fflush(stdout);
    command_dispatch(persisted_plan);
  }

  ////////////////////////////////////////////////////////////////////////////
  /// Command buffer for received request
  char request[RESTAT_REQ_LEN] = {0};

  while (true) {
    ////////////////////////////////////////////////////////////////////////////
    /// Run non-blocking timings
    relay_tick();
    buzzer_tick();

    ////////////////////////////////////////////////////////////////////////////
    /// Fetch and process channel command request
    if (parser_get_command(request, RESTAT_REQ_LEN)) {
      command_dispatch(request);
      memset(request, 0, RESTAT_REQ_LEN * sizeof(char));
    }
  }

  return 0;
}
