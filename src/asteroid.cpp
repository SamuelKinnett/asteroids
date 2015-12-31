#include "asteroid.h"
#include <iostream>

Asteroid::Asteroid(float x, float y) {
	
	this->worldPosition.SetX(x);
	this->worldPosition.SetY(y);

	this->GenerateAsteroid();
	this->RecalculateBB();
}

Asteroid::~Asteroid() {

}

void Asteroid::Update() {
	//TODO
}

void Asteroid::Move(float x, float y) {
	this->worldPosition.SetX(x);
	this->worldPosition.SetY(y);
}

void Asteroid::Render() {
	float tempX = this->worldPosition.GetX();
	float tempY = this->worldPosition.GetY();

	glBegin(GL_LINE_LOOP);
	for(int currentPoint = 0; currentPoint < 8; ++ currentPoint)
		glVertex2f(tempX + asteroidPoints[currentPoint].GetX(),
			tempY + asteroidPoints[currentPoint].GetY());
	glEnd();
	
}

bool Asteroid::AABB(GameObject* target) {
	//TODO
}

bool Asteroid::SAT(GameObject* target) {
	//TODO
}

void Asteroid::Collide() {
	//TODO
}

void Asteroid::RecalculateBB() {
	//TODO
}

//Displaces an 8 point polygon such that it resembles an asteroid
void Asteroid::GenerateAsteroid() {

	srand(time(NULL));

	//Bottom left
	float randMod = ((rand() % 60) - 30.0f) / 100.0f;
	asteroidPoints[0].SetX(-0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[0].SetY(-0.5f + randMod);

	//Bottom centre
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[1].SetX(0.0f);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[1].SetY(-0.5f + randMod);
	
	//Bottom right
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[2].SetX(0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[2].SetY(-0.5f + randMod);
	
	//Right
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[3].SetX(0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[3].SetY(0.0f);
	
	//Top right
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[4].SetX(0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[4].SetY(0.5f + randMod);
	
	//Top centre
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[5].SetX(0.0f);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[5].SetY(0.5f + randMod);
	
	//Top left
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[6].SetX(-0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[6].SetY(0.5f + randMod);
	
	//Left
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[7].SetX(-0.5f + randMod);
	randMod = ((rand() % 30) - 30.0f) / 100.0f;
	asteroidPoints[7].SetY(0.0f);
	
}
