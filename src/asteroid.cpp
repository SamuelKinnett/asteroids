#include "asteroid.h"

Asteroid::Asteroid() {
	GenerateAsteroid();
	RecalculateBB();
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
	//TODO
}

bool Asteroid::AABB(GameObject* target) {
	//TODO
}

bool Asteroid::SAT(GameObject* target) {
	//TODO
}

void Asteroid::RecalculateBB() {
	//TODO
}

//Displaces an 8 point polygon such that it resembles an asteroid
void Asteroid::GenerateAsteroid() {

	//Bottom left
	float randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(-0.5f + randMod);
	asteroidPoints[0].SetY(-0.5f + randMod);

	//Bottom centre
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(0.0f);
	asteroidPoints[0].SetY(-0.5f + randMod);
	
	//Bottom right
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(0.5f + randMod);
	asteroidPoints[0].SetY(-0.5f + randMod);
	
	//Right
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(0.5f + randMod);
	asteroidPoints[0].SetY(0.0f);
	
	//Top right
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(0.5f + randMod);
	asteroidPoints[0].SetY(0.5f + randMod);
	
	//Top centre
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(0.0f);
	asteroidPoints[0].SetY(0.5f + randMod);
	
	//Top left
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(-0.5f + randMod);
	asteroidPoints[0].SetY(0.5f + randMod);
	
	//Left
	randMod = ((rand() % 30) - 30) / 100;
	asteroidPoints[0].SetX(-0.5f + randMod);
	asteroidPoints[0].SetY(0.0f);
	
}
