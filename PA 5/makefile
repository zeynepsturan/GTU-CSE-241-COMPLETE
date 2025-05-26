#compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

#executable file
TARGET = program

#source files
SRCS = main.cpp Catalog.cpp Item.cpp

#object files
OBJS = $(SRCS:.cpp=.o)

#default target
all: $(TARGET)

#making the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#creating object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#run the executable
run: $(TARGET)
	./$(TARGET)

#cleaning
clean:
	rm -f $(OBJS) $(TARGET)
