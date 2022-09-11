CXX=g++
CXXFLAGS=-std=c++17 -ggdb -Wall
LIBS=-lfmt

AR=ar
ARFLAGS=rc

SRC=$(wildcard src/*.cpp)
OBJS=$(addprefix obj/, $(SRC:.cpp=.o))

.PHONY: dirs clean

all: dirs target example

example: target
	$(CXX) $(CXXFLAGS) -Isrc example.cpp $(LIBS) -Llib -ljason

target: $(OBJS)
	$(AR) $(ARFLAGS) lib/libjason.a $^

obj/src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	mkdir -p obj/src lib

clean:
	-rm -rf obj/src lib a.out libjason.a
