CC = gcc
CXX = g++
RM = rm -f

OBJS = main.o vector2D.o
LDLIBS = -lGL -lGLU -lglut
ARGS = -std=c++11 -Wall -g

all: asteroids

asteroids: $(OBJS)
	$(CXX) $(ARGS) -o ../bin/asteroids $(OBJS) $(LDLIBS)

main.o: main.cpp main.h
	$(CXX) $(ARGS) -c main.cpp -o main.o

vector2D.o: vector2D.cpp vector2D.h
	$(CXX) $(ARGS) -c vector2D.cpp -o vector2D.o

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) ../bin/asteroids
