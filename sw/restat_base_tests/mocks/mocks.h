#pragma once

#include <queue>
#include <vector>
#include <string>
#include <stdint.h>
#include <stdbool.h>

// Mock queue for getchar_timeout_us
extern std::queue<char> mock_input_queue;
void mock_push_input(const std::string& str);
void mock_clear_input();

// Mock call registry for relay
struct RelayMockCall {
    enum CallType {
        SET, SET_ALL, TIMER
    } type;
    uint32_t channel;
    bool state;
    uint32_t timer_ms;
    bool timer_start_on;
};

extern std::vector<RelayMockCall> relay_calls;
void mock_clear_relay_calls();
void mock_set_channel_status(uint32_t channel, const std::string& status);

// Mock states for buzzer, status_led, watchdog, persist
extern bool buzzer_beep_stop_called;
extern uint8_t mock_led_r;
extern uint8_t mock_led_g;
extern uint8_t mock_led_b;
extern bool watchdog_reboot_called;
extern std::string last_saved_plan;

void mock_clear_system_states();
