CC = gcc-15
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS) -O3 -fopenmp
LDFLAGS = -fopenmp

BUILD_DIR = build
SOURCES = parallel.c 
OBJECTS = $(BUILD_DIR)/parallel.o
TARGET = $(BUILD_DIR)/main

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
