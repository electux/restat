/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ws2812.pio.h
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

#if !PICO_NO_HARDWARE
#include "hardware/clocks.h"
#include "hardware/pio.h"

#endif

////////////////////////////////////////////////////////////////////////////
/// @brief PIO program instructions for WS2812
static const uint16_t ws2812_program_instructions[] = {
    //     .wrap_target
    0x6221, //  0: out    x, 1            side 0 [2]
    0x1123, //  1: jmp    !x, 3           side 1 [1]
    0x1400, //  2: jmp    0               side 1 [4]
    0xa442, //  3: nop                    side 0 [4]
            //     .wrap
};

#if !PICO_NO_HARDWARE

////////////////////////////////////////////////////////////////////////////
/// @brief PIO program instruction structure for WS2812
static const struct pio_program ws2812_program = {
    .instructions = ws2812_program_instructions,
    .length = 4,
    .origin = -1,
};

////////////////////////////////////////////////////////////////////////////
/// @brief Prepares default configuration
/// @param offset represents programm address
/// @return PIO configuration structure for WS2812
static inline pio_sm_config ws2812_program_get_default_config(uint offset) {
  const uint wrap_target_val = 0;
  const uint wrap_val = 3;

  pio_sm_config config = pio_get_default_sm_config();
  uint wrap_target = offset + wrap_target_val;
  uint wrap = offset + wrap_val;

  sm_config_set_wrap(&config, wrap_target, wrap);
  sm_config_set_sideset(&config, 1, false, false);

  return config;
}

////////////////////////////////////////////////////////////////////////////
/// @brief WS2812 init structure
typedef struct _ws2812_init {
  PIO pio;
  uint sm;
  uint offset;
  uint pin;
  float freq;
  bool rgbw;
} ws2812_init;

////////////////////////////////////////////////////////////////////////////
/// @brief Performs WS2812 program initialization
/// @param init represents pointer to WS2812 init structure
static inline void ws2812_program_init(ws2812_init *init) {
  const int t1 = 2;
  const int t2 = 5;
  const int t3 = 3;

  pio_gpio_init(init->pio, init->pin);
  pio_sm_set_consecutive_pindirs(init->pio, init->sm, init->pin, 1, true);

  pio_sm_config config = ws2812_program_get_default_config(init->offset);

  sm_config_set_sideset_pins(&config, init->pin);
  sm_config_set_out_shift(&config, false, true, init->rgbw ? 32 : 24);
  sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

  int cycles_per_bit = (t1 + t2 + t3);
  float div = clock_get_hz(clk_sys) / (init->freq * cycles_per_bit);

  sm_config_set_clkdiv(&config, div);
  pio_sm_init(init->pio, init->sm, init->offset, &config);
  pio_sm_set_enabled(init->pio, init->sm, true);
}

#endif

////////////////////////////////////////////////////////////////////////////
/// @brief PIO program instructions for WS2812 (parallel)
static const uint16_t ws2812_parallel_program_instructions[] = {
    //     .wrap_target
    0x6020, //  0: out    x, 32
    0xa10b, //  1: mov    pins, !null            [1]
    0xa401, //  2: mov    pins, x                [4]
    0xa103, //  3: mov    pins, null             [1]
            //     .wrap
};

#if !PICO_NO_HARDWARE

////////////////////////////////////////////////////////////////////////////
/// @brief PIO program instruction structure for WS2812 (parallel)
static const struct pio_program ws2812_parallel_program = {
    .instructions = ws2812_parallel_program_instructions,
    .length = 4,
    .origin = -1,
};

////////////////////////////////////////////////////////////////////////////
/// @brief Prepares default configuration (parallel)
/// @param offset represents program address
/// @return PIO configuration structure for WS2812
static inline pio_sm_config
ws2812_parallel_program_get_default_config(uint offset) {
  const uint wrap_target_val = 0;
  const uint wrap_val = 3;

  pio_sm_config config = pio_get_default_sm_config();
  uint wrap_target = offset + wrap_target_val;
  uint wrap = offset + wrap_val;
  sm_config_set_wrap(&config, wrap_target, wrap);

  return config;
}

////////////////////////////////////////////////////////////////////////////
/// @brief WS2812 parallel init structure
typedef struct _ws2812_parallel_init {
  PIO pio;
  uint sm;
  uint offset;
  uint pin_base;
  uint pin_count;
  float freq;
} ws2812_parallel_init;

////////////////////////////////////////////////////////////////////////////
/// @brief Performs WS2812 parallel program initialization
/// @param init represents pointer to WS2812 parallel init structure
static inline void ws2812_parallel_program_init(ws2812_parallel_init *init) {
  const int t1 = 2;
  const int t2 = 5;
  const int t3 = 3;

  uint max_pin_count = init->pin_base + init->pin_count;

  for (uint i = init->pin_base; i < max_pin_count; i++) {
    pio_gpio_init(init->pio, i);
  }

  pio_sm_set_consecutive_pindirs(
      init->pio, init->sm, init->pin_base, init->pin_count, true
  );

  pio_sm_config config =
      ws2812_parallel_program_get_default_config(init->offset);

  sm_config_set_out_shift(&config, true, true, 32);
  sm_config_set_out_pins(&config, init->pin_base, init->pin_count);
  sm_config_set_out_pins(&config, init->pin_base, init->pin_count);
  sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);

  int cycles_per_bit = (t1 + t2 + t3);

  float div = clock_get_hz(clk_sys) / (init->freq * cycles_per_bit);

  sm_config_set_clkdiv(&config, div);
  pio_sm_init(init->pio, init->sm, init->offset, &config);
  pio_sm_set_enabled(init->pio, init->sm, true);
}

#endif
