# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Source and Object Files
SRCS = Audio.cpp Dataset.cpp Image.cpp main.cpp Media.cpp Player.cpp Viewer.cpp Text.cpp Video.cpp
OBJS = $(SRCS:.cpp=.o)

# Executable Name
TARGET = main

# Default target
all: $(TARGET)

# Link all object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
