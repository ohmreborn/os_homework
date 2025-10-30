CC = gcc
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS) -O3 -fopenmp -lm
LDFLAGS = -fopenmp

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
INC_DIR = include
HEADERS = $(INC_DIR)/config.h
OBJECTS = $(BUILD_DIR)/parallel.o

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $< 

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
