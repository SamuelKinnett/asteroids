CC = gcc
CXX = g++
RM = rm -f

OBJS = main.0
LDLIBS = -lGL -lGLU -lglut
ARGS = -std=c++11 -Wall -g

all: asteroids

asteroids: $(OBJS)
	$(CXX) $(ARGS) -o ../bin/asteroids $(OBJS) $(LDLIBS)

main.o: main.cpp main.h
	$(CXX) $(ARGS) -c main.cpp -o main.o

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) ../bin/asteroids
