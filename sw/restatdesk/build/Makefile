#
# @brief   restatdesk
# @version 1.1.6
# @date    2024-07-21 16:05:11.326670
# @company None, free software to use 2024
# @author  Vladimir Roncevic <elektron.ronca@gmail.com>
#

include toolchain.mk
include cxxflags.mk
include odflags.mk
include csflags.mk
include sources.mk
include objects.mk

GTK_CFLAGS := $(shell pkg-config --cflags gtkmm-4.0)
GTK_LIBS   := $(shell pkg-config --libs gtkmm-4.0)

EXECUTABLE = restatdesk

LSS = \
	$(EXECUTABLE).lss

SIZEDUMMY = \
	sizedummy

CLEAN_LIST = \
	$(OBJECTS) \
	$(EXECUTABLE) \
	$(LSS) \
	../resources.cc

.PHONY: all debug release clean sizedummy coredump-setup run-debug

all: $(EXECUTABLE) $(LSS) $(SIZEDUMMY)

debug:
	$(MAKE) all OPT_FLAGS="-g"

release:
	$(MAKE) all OPT_FLAGS="-O2"

../resources.cc: ../resources.gresource.xml ../style.css
	@echo 'Generating resources.cc from gresource xml'
	glib-compile-resources --sourcedir=.. --target=../resources.cc --generate-source ../resources.gresource.xml

.cc.o:
	@echo 'Invoking: compile unit $<'
	$(CXX) $(CXXFLAGS) $(GTK_CFLAGS) -o $@ $<
	@echo 'Finished compile unit $<'
	@echo ' '

$(EXECUTABLE): $(OBJECTS)
	@echo 'Invoking: link executable $@'
	$(CXX) $(OBJECTS) $(GTK_LIBS) -o $@
	@echo 'Finished link process: $@'
	@echo ' '

$(EXECUTABLE).lss: $(EXECUTABLE)
	@echo 'Invoking: Display information from object $@'
	$(OD) $(ODFLAGS) $(EXECUTABLE) > "$(EXECUTABLE).lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: $(EXECUTABLE)
	@echo 'Invoking: Displays the sizes of sections inside $@'
	$(CS) $(CSFLAGS) $(EXECUTABLE)
	@echo 'Finished building: $@'
	@echo ' '

clean:
	@echo 'Invoking: clean up project structure'
	@for item in $(CLEAN_LIST); do \
	if [ -e "$$item" ]; then \
		echo "$(RM) $$item"; \
		$(RM) $$item; \
	fi; \
	done
	@echo 'Finished clean up'
	@echo ' '

run-debug: $(EXECUTABLE)
	ulimit -c unlimited && ./$(EXECUTABLE)