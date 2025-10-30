CC = gcc-15
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS) -O3

BUILD_DIR = build
SOURCES = cow.c 
OBJECTS = $(BUILD_DIR)/cow.o
TARGET = $(BUILD_DIR)/main

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
