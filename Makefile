# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Target executable
TARGET = wordlehelper

# Source and header files
SRC = helper.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = helper.h

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)

# Run rule (optional)
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
