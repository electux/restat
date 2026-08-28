/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * persist.c
 * Copyright (C) 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <device/persist.h>
#include <hardware/flash.h>
#include <hardware/sync.h>
#include <string.h>

#define FLASH_TARGET_OFFSET (1536 * 1024) // 1.5 MB offset

void persist_save_plan(const char *plan_str) {
  // Prepare a page buffer (256 bytes) to write
  uint8_t write_buf[FLASH_PAGE_SIZE];
  memset(write_buf, 0, sizeof(write_buf));

  // Copy plan_str to buffer
  strncpy((char *)write_buf, plan_str, sizeof(write_buf) - 1);

  // Disable interrupts before erasing and writing
  uint32_t ints = save_and_disable_interrupts();

  // Erase one sector (4096 bytes) at the target offset
  flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);

  // Write one page (256 bytes)
  flash_range_program(FLASH_TARGET_OFFSET, write_buf, FLASH_PAGE_SIZE);

  // Restore interrupts
  restore_interrupts(ints);
}

bool persist_load_plan(char *buf, size_t max_len) {
  // Flash is mapped to memory starting at XIP_BASE (0x10000000)
  const uint8_t *flash_target_contents = (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET);

  // Check if it starts with a valid pattern
  if (strncmp((const char *)flash_target_contents, "rs#all#plan#", 12) == 0) {
    strncpy(buf, (const char *)flash_target_contents, max_len - 1);
    buf[max_len - 1] = '\0';
    return true;
  }
  return false;
}
