#
# @brief   command library setup
# @version v1.0.0
# @date    2026-08-21
#

add_library(command parser.c command_tbl.c)
target_include_directories(command PUBLIC .)
target_link_libraries(command device pico_stdlib)
