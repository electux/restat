/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_gpio.c
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
#include <io_gpio.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h>

void io_gpio_init(uint32_t pin, bool is_output) {
  gpio_init(pin);
  if (is_output) {
    gpio_set_dir(pin, GPIO_OUT);
  } else {
    gpio_set_dir(pin, GPIO_IN);
  }
}

void io_gpio_write(uint32_t pin, bool value) {
  gpio_put(pin, value);
}

bool io_gpio_read(uint32_t pin) {
  return gpio_get(pin);
}
