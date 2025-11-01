CXX = g++-14
DEBUGFLAGS = -Wall
CFLAGS = -fopenmp $(DEBUGFLAGS) -O3 -std=c++11
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
	$(CXX) -o $@ $< $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) -I$(INC_DIR) -o $@ -c $< 

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
