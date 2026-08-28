#
# @brief   restatdesk toolchain
# @version 1.1.6
# @date    2024-07-21 16:05:11.344555
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

RM = rm
OD = objdump
CS = size

COMPILER = gcc
#COMPILER = clang

ifeq ($(COMPILER), gcc)
    CXX = g++
else ifeq ($(COMPILER), clang)
    CXX = clang++
else
    $(error Unknown COMPILER: $(COMPILER))
endif
