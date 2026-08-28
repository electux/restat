#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void watchdog_reboot(uint32_t pc, uint32_t sp, uint32_t delay_ms);

#ifdef __cplusplus
}
#endif
