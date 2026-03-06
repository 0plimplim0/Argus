CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -I./include
SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.cc $(SRC_DIR)/analyzer.cc $(SRC_DIR)/utils.cc
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/analyzer.o $(BUILD_DIR)/utils.o
TARGET = $(BUILD_DIR)/argus

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
