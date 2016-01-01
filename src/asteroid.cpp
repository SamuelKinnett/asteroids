#include "asteroid.h"
#include <iostream>

Asteroid::Asteroid(float x, float y) {
	
	this->worldPosition.SetX(x);
	this->worldPosition.SetY(y);
	this->GenerateAsteroid();
	this->RecalculateBB();

	size = 2;

	float xMagnitude, yMagnitude, xMod, yMod;
	xMagnitude = (rand() % 2 + 1) / 500.0f;	
	yMagnitude = (rand() % 2 + 1) / 500.0f;	
	
	if (rand() % 10 < 5)
		xMod = 1;
	else
		xMod = -1;

	if (rand() % 10 < 5)
		yMod = 1;
	else
		yMod = -1;

	this->moveVector.SetX(xMagnitude * xMod);
	this->moveVector.SetY(yMagnitude * yMod);
}

Asteroid::~Asteroid() {

}

void Asteroid::Update() {
	
	float posX = this->worldPosition.GetX();
	float posY = this->worldPosition.GetY();

	//Rotate the asteroid
	this->Rotate(rotationAmount);
	
	//Move the asteroid
	posX += this->moveVector.GetX();
	posY += this->moveVector.GetY();
	this->SetPosition(posX, posY);

	//Check to see if the asteroid is "off screen". If it is, teleport
	//it to just off screen on the opposite side, such that it "wraps 
	//around".
	
	bool offScreen = true;

	for (int i = 0; i < 8; ++i) {
		float pointX = this->asteroidPoints[i].GetX();
		float pointY = this->asteroidPoints[i].GetY();

		if (posX + pointX < 1.0f 
			&& posX + pointX > -1.0f
			&& posY + pointY < 1.0f
			&& posY + pointY > -1.0f) {
			
			//The point is on screen
			offScreen = false;
			break;
		}	
			
	}

	//TODO: Intelligently place the asteroids on the opposite side so
	//that there is never a "sudden appearance", but rather the asteroid
	//smoothly transitions

	if (offScreen) {
		float newX, newY;
		if (posX > 1.0f) {
			//The asteroid has gone off the right of the screen
			newX = -0.99f;
			newY = posY;
		} else if (posX < -1.0f) {
			//The asteroid has gone off the left of the screen
			newX = 0.99f;
			newY = posY;
		} else if (posY > 1.0f) {
			//The asteroid has gone off the top of the screen
			newX = posX;
			newY = -0.99f;
		} else if (posY < -1.0f) {
			//The asteroid has gone off the bottom of the screen
			newX = posX;
			newY = 0.99f;
		} else {
			std::cout << "What hte fug" << std::endl;
			std::cout << "X: " << posX << std::endl;
			std::cout << "Y: " << posY << std::endl;
			newX = 0;
			newY = 0;
		}
		this->SetPosition(newX, newY);

	}
}

void Asteroid::SetMoveVector(Vector2D* newVector) {
	this->moveVector = *newVector;
}

void Asteroid::Rotate(float angle) {
	for (int currentPoint = 0; currentPoint < 8; ++ currentPoint) {
		asteroidPoints[currentPoint].Rotate(angle,
			       			new Vector2D(0, 0));
	}
}

void Asteroid::SetPosition(float x, float y) {
	this->worldPosition.SetX(x);
	this->worldPosition.SetY(y);
}

void Asteroid::Render() {
	float tempX = this->worldPosition.GetX();
	float tempY = this->worldPosition.GetY();

	glBegin(GL_LINE_LOOP);
	for(int currentPoint = 0; currentPoint < 8; ++ currentPoint)
		glVertex2f(tempX + this->asteroidPoints[currentPoint].GetX(),
			tempY + this->asteroidPoints[currentPoint].GetY());
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

void Asteroid::ApplyGravity(GameObject* target) {
	float newX, newY, posX, posY, targetX, targetY;

	posX = this->worldPosition.GetX();
	posY = this->worldPosition.GetY();
	targetX = target->GetPosition()->GetX();
	targetY = target->GetPosition()->GetY();

	newX = ((targetX - posX) * target->GetMass());
	newY = ((targetY - posY) * target->GetMass());

	this->moveVector.SetX(this->moveVector.GetX() + newX);
	this->moveVector.SetY(this->moveVector.GetY() + newY);
}

Vector2D* Asteroid::GetPosition() {
	return &this->worldPosition;
}

float Asteroid::GetMass() {
	return this->mass;
}

void Asteroid::SetMass(float mass) {
	this->mass = mass;
}

void Asteroid::RecalculateBB() {
	//TODO
}

//Displaces an 8 point polygon such that it resembles an asteroid
void Asteroid::GenerateAsteroid() {

	float defaultValue = 0.05f;
	float upperBound = 30.0f;
	float lowerBound = -30.0f;
	float divisor = 1000.0f;

	mass = 0.00001f;

	//Set a random rotation amount
	rotationAmount = ((rand() % 4) - 2.0f) / 10.0f;

	//Bottom left
	float randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[0].SetX(-defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[0].SetY(-defaultValue + randMod);

	//Bottom centre
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[1].SetX(0.0f);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[1].SetY(-defaultValue + randMod);
	
	//Bottom right
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[2].SetX(defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[2].SetY(-defaultValue + randMod);
	
	//Right
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[3].SetX(defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[3].SetY(0.0f);
	
	//Top right
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[4].SetX(defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[4].SetY(defaultValue + randMod);
	
	//Top centre
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[5].SetX(0.0f);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[5].SetY(defaultValue + randMod);
	
	//Top left
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[6].SetX(-defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[6].SetY(defaultValue + randMod);
	
	//Left
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[7].SetX(-defaultValue + randMod);
	randMod = ((rand() % (int)upperBound) + lowerBound) / divisor;
	asteroidPoints[7].SetY(0.0f);
	
}
