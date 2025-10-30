CC = gcc-15
DEBUGFLAGS = -Wall
CFLAGS = $(DEBUGFLAGS) -O3 -fopenmp
LDFLAGS = -fopenmp -lm

BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
INC_DIR = include
HEADERS = $(INC_DIR)/config.h
OBJECTS = $(BUILD_DIR)/parallel.o

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir build

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $< $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $< 

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
