COMPILER = g++
CFLAGS = -Wall
LDFLAGS = -lm

BUILD_DIR = build

HEADER  = ./include/config.h
HEADER += ./include/read_ini_file.h
HEADER += ./include/read_ini_file.cpp
HEADER += ./include/pendulum_system.h
HEADER += ./include/pendulum_system.cpp
HEADER += ./include/controller.h
HEADER += ./include/controller.cpp
HEADER += ./include/DataLog.h
HEADER += ./include/DataLog.cpp

.PHONY: all clean

all: $(BUILD_DIR) $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(BUILD_DIR)/main.o
	$(COMPILER) $(CFLAGS) -o $@ $^ $(HEADER) $(LDFLAGS)

$(BUILD_DIR)/main.o: main.cpp
	$(COMPILER) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: $(BUILD_DIR)
	rm build/*