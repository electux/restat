#
# @brief   device library setup
# @version v1.0.0
# @date    2026-08-21
#

add_library(device relay.c buzzer.c status_led.c persist.c)
target_include_directories(device PUBLIC .)
target_link_libraries(device io ws2812 pico_stdlib hardware_pio hardware_flash)
