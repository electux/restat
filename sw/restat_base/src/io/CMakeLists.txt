#
# @brief   io library setup
# @version v1.0.0
# @date    2026-08-21
#

add_library(io io_gpio.c io_pwm.c)
target_include_directories(io PUBLIC .)
target_link_libraries(io pico_stdlib hardware_gpio hardware_pwm)
