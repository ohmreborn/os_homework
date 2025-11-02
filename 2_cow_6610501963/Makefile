CC = gcc
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS)

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main

OBJECTS = $(BUILD_DIR)/cow.o

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $<

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

run: all
	$(TARGET) $(MEM)

clean:
	rm -rf $(BUILD_DIR)
