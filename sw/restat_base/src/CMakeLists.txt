#
# @brief   restat-base setup output files
# @version v1.0.3
# @date    2021-12-15
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

# Prepares PIO target for WS2812 (headers and implementation)
pico_simple_hardware_target(pio)

# Enable verbose logging globally
add_compile_definitions(VERBOSE)

# Adds sub-structure includes
include_directories(.)
include_directories(io)
include_directories(ws2812)
include_directories(device)
include_directories(command)

# Adds sub-structure sources
add_subdirectory(io)
add_subdirectory(ws2812)
add_subdirectory(device)
add_subdirectory(command)

# Sets executable
add_executable("${CMAKE_PROJECT_NAME}" main.c)

# Enables USB output
pico_enable_stdio_usb("${CMAKE_PROJECT_NAME}" 1)

# Disables UART output
pico_enable_stdio_uart("${CMAKE_PROJECT_NAME}" 0)

# Links all libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" command device io ws2812)

# Creates extra output files map/bin/hex
pico_add_extra_outputs("${CMAKE_PROJECT_NAME}")

# Adds URL via pico_set_program_url
pro_auto_set_url("${CMAKE_PROJECT_NAME}")
