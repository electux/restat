#
# @brief   restat-base ws2812 pio
# @version v1.0.3
# @date    2023-09-05
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Adds WS2812 target library as interface (header-only)
add_library(ws2812 INTERFACE)
target_include_directories(ws2812 INTERFACE .)
