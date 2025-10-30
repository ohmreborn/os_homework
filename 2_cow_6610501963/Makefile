CC = gcc-15
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS) -O3

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

OBJECTS = $(BUILD_DIR)/cow.o
INC_DIR = include
HEADERS = $(INC_DIR)/config.h

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $<

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
