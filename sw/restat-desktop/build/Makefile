#
# @brief   restat-desktop
# @version 1.0.0
# @date    Mon 13 Dec 2021 11:45:04 PM CET
# @company None, free software to use 2021
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

CC=g++
RM=rm

include ccflags.mk
include ldflags.mk
include sources.mk
include objects.mk

EXECUTABLE=restat-desktop

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ `pkg-config gtkmm-3.0 --libs`

.cc.o:
	$(CC) $(CFLAGS) $< -o $@ `pkg-config gtkmm-3.0 --cflags`

clean:
	$(RM) -rf ../*.o $(EXECUTABLE)
