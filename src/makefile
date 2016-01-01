CC = gcc
CXX = g++
RM = rm -f

OBJS = main.o vector2D.o asteroid.o player.o
LDLIBS = -lGL -lGLU -lglut
ARGS = -std=c++11 -Wall -g

all: asteroids

asteroids: $(OBJS)
	$(CXX) $(ARGS) -o ../bin/asteroids $(OBJS) $(LDLIBS)

main.o: main.cpp main.h gameobject.h
	$(CXX) $(ARGS) -c main.cpp -o main.o

vector2D.o: vector2D.cpp vector2D.h
	$(CXX) $(ARGS) -c vector2D.cpp -o vector2D.o

asteroid.o: asteroid.cpp asteroid.h gameobject.h
	$(CXX) $(ARGS) -c asteroid.cpp -o asteroid.o

player.o: player.cpp player.h gameobject.h
	$(CXX) $(ARGS) -c player.cpp -o player.o

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) ../bin/asteroids
