#
# @brief   restatdesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.297462
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

OPT_FLAGS ?= -Og -g

ifeq ($(CXX), g++)
CXXFLAGS = \
	-std=c++23 \
	-c \
	$(OPT_FLAGS) \
	-pedantic \
	-Wall \
	-Wextra \
	-Wconversion \
	-Wnull-dereference \
	-Wnon-virtual-dtor \
	-Wsuggest-override \
	-Wcast-align \
	-Wcast-qual \
	-Wdisabled-optimization \
	-Wformat=2 \
	-Winit-self \
	-Wlogical-op \
	-Wmissing-declarations \
	-Wmissing-include-dirs \
	-Wnoexcept \
	-Woverloaded-virtual \
	-Wshadow \
	-Wsign-promo \
	-Wstrict-null-sentinel \
	-Wstrict-overflow=5 \
	-Wundef \
	-Werror \
	-Wno-unused \
	-I..
else ifeq ($(CXX), clang++)
CXXFLAGS = \
    -std=c++23 \
    -c \
    $(OPT_FLAGS) \
    -pedantic \
    -Wall \
    -Wextra \
    -Wcast-align \
    -Wcast-qual \
    -Wformat=2 \
    -Winit-self \
    -Wmissing-declarations \
    -Wmissing-include-dirs \
    -Woverloaded-virtual \
    -Wshadow \
    -Wsign-conversion \
    -Wstrict-overflow=5 \
	-Wno-error=sign-conversion \
	-Wno-error=unused-const-variable \
    -Wundef \
    -Werror \
    -Wunused \
    -v \
	-I..
else
	$(error Unsupported compiler: $(CXX))
endif
