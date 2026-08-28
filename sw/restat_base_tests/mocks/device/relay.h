#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum { RELAY_NUM_CHANNELS = 8 };

typedef enum {
  RELAY_MODE_TOGGLE,
  RELAY_MODE_TIMER
} relay_mode_t;

bool relay_init(void);
void relay_set(uint32_t channel, bool state);
void relay_set_all(bool state);
void relay_start_timer(uint32_t channel, uint32_t milliseconds, bool start_on);
void relay_tick(void);
void relay_get_status(uint32_t channel, char *buf, uint32_t max_len);

#ifdef __cplusplus
}
#endif
