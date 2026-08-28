#include "mocks.h"
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include "device/relay.h"
#include "device/buzzer.h"
#include "device/status_led.h"
#include "device/persist.h"
#include <cstdio>
#include <cstring>

std::queue<char> mock_input_queue;
std::vector<RelayMockCall> relay_calls;
static std::string channel_statuses[RELAY_NUM_CHANNELS];

bool buzzer_beep_stop_called = false;
uint8_t mock_led_r = 0;
uint8_t mock_led_g = 0;
uint8_t mock_led_b = 0;
bool watchdog_reboot_called = false;
std::string last_saved_plan;

void mock_push_input(const std::string& str) {
    for (char c : str) {
        mock_input_queue.push(c);
    }
}

void mock_clear_input() {
    std::queue<char> empty;
    std::swap(mock_input_queue, empty);
}

void mock_clear_relay_calls() {
    relay_calls.clear();
}

void mock_set_channel_status(uint32_t channel, const std::string& status) {
    if (channel < RELAY_NUM_CHANNELS) {
        channel_statuses[channel] = status;
    }
}

void mock_clear_system_states() {
    buzzer_beep_stop_called = false;
    mock_led_r = 0;
    mock_led_g = 0;
    mock_led_b = 0;
    watchdog_reboot_called = false;
    last_saved_plan.clear();
    for (uint32_t i = 0; i < RELAY_NUM_CHANNELS; i++) {
        channel_statuses[i].clear();
    }
}

extern "C" {

int16_t getchar_timeout_us(uint32_t timeout_us) {
    (void)timeout_us;
    if (mock_input_queue.empty()) {
        return PICO_ERROR_TIMEOUT;
    }
    char c = mock_input_queue.front();
    mock_input_queue.pop();
    return (int16_t)(uint8_t)c;
}

void watchdog_reboot(uint32_t pc, uint32_t sp, uint32_t delay_ms) {
    (void)pc;
    (void)sp;
    (void)delay_ms;
    watchdog_reboot_called = true;
}

bool relay_init(void) {
    return true;
}

void relay_set(uint32_t channel, bool state) {
    RelayMockCall call = {RelayMockCall::SET, channel, state, 0, false};
    relay_calls.push_back(call);
}

void relay_set_all(bool state) {
    RelayMockCall call = {RelayMockCall::SET_ALL, 0, state, 0, false};
    relay_calls.push_back(call);
}

void relay_start_timer(uint32_t channel, uint32_t milliseconds, bool start_on) {
    RelayMockCall call = {RelayMockCall::TIMER, channel, false, milliseconds, start_on};
    relay_calls.push_back(call);
}

void relay_tick(void) {
    // No-op
}

void relay_get_status(uint32_t channel, char *buf, uint32_t max_len) {
    if (channel < RELAY_NUM_CHANNELS) {
        if (!channel_statuses[channel].empty()) {
            snprintf(buf, max_len, "%s", channel_statuses[channel].c_str());
        } else {
            snprintf(buf, max_len, "channel %u: OFF", channel + 1);
        }
    }
}

void buzzer_beep_stop(void) {
    buzzer_beep_stop_called = true;
}

void status_led_write(uint8_t r, uint8_t g, uint8_t b) {
    mock_led_r = r;
    mock_led_g = g;
    mock_led_b = b;
}

void persist_save_plan(const char *plan) {
    last_saved_plan = plan;
}

}
