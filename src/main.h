#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
//Compiling on NSA/Windows, include windows.h
#include <Windows.h>
#endif
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>
#include <iostream>

//Custom classes
#include "gameobject.h"
#include "asteroid.h"
#include "player.h"

//Method definitions
void Initialise(int, char*[]);
void InitWindow(int, char*[]);
bool InitOpenGL();
void Update();
void Render();
void Resize(int, int);
void MainLoop(int);

//Input handling
void HandleMouseClick(int, int, int, int);
void HandleMouseMoving(int, int);
void HandleButtonPress(unsigned char, int, int);
void HandleSpecialButtonPress(int, int, int);

#endif
