#compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

#executable file
TARGET = simulation

#source files
SRCS = main.cpp robot.cpp humanic.cpp world.cpp optimusprime.cpp robocop.cpp roomba.cpp bulldozer.cpp kamikaze.cpp

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
