# Define the output directory relative to the project root, and quote it to handle spaces
BUILD_DIR := ../../build/stemdump

# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11

# List of source files
SRCS := $(wildcard *.cpp)

# List of object files (replace .cpp with .o)
OBJS := $(SRCS:.cpp=.o)

# Target executable name
TARGET := stemdump

# Default target
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	@mkdir -p "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -o "$(BUILD_DIR)/$@" $(addprefix "$(BUILD_DIR)/",$(OBJS))

# Rule to compile each source file into object files
%.o: %.cpp
	@mkdir -p "$(BUILD_DIR)"
	$(CXX) $(CXXFLAGS) -c $< -o "$(BUILD_DIR)/$@"

# Phony target to clean object files and executable
clean:
	rm -rf "$(BUILD_DIR)/*.o" "$(BUILD_DIR)/$(TARGET)"

# Ensure 'clean' is not treated as a file
.PHONY: all clean
