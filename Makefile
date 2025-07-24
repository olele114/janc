CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror

OBJS = $(wildcard ./src/*.cpp ./src/*.hpp)
TARGET = janc.out

janc: 
	$(CXX) $(CXXFLAGS) $(TARGET) $(OBJS)
