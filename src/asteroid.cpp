#include "asteroid.h"
#include <iostream>

Asteroid::Asteroid(float x, float y) {
	
	worldPosition.SetX(x);
	worldPosition.SetY(y);
	GenerateAsteroid();
	RecalculateBB();

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

	moveVector.SetX(xMagnitude * xMod);
	moveVector.SetY(yMagnitude * yMod);
}

Asteroid::~Asteroid() {

}

void Asteroid::Update() {
	
	float posX = worldPosition.GetX();
	float posY = worldPosition.GetY();

	//Rotate the asteroid
	Rotate(rotationAmount);
	
	//Move the asteroid
	posX += moveVector.GetX();
	posY += moveVector.GetY();
	SetPosition(posX, posY);

	//Move the bounding box
	boundingBox[0] += moveVector.GetX();
	boundingBox[2] += moveVector.GetX();
	boundingBox[1] += moveVector.GetY();
	boundingBox[3] += moveVector.GetY();

	//Check to see if the asteroid is "off screen". If it is, teleport
	//it to just off screen on the opposite side, such that it "wraps 
	//around".
	
	bool offScreen = true;

	if (boundingBox[2] > -1
		&& boundingBox[0] < 1
		&& boundingBox[3] > -1
		&& boundingBox[1] < 1)
		offScreen = false;

	/* OLD METHOD
	for (int i = 0; i < 8; ++i) {
		float pointX = asteroidPoints[i].GetX();
		float pointY = asteroidPoints[i].GetY();

		if (posX + pointX < 1.0f 
			&& posX + pointX > -1.0f
			&& posY + pointY < 1.0f
			&& posY + pointY > -1.0f) {
			
			//The point is on screen
			offScreen = false;
			break;
		}	
			
	}
	*/

	if (offScreen) {
		if (boundingBox[2] < -1) {
			//The asteroid has gone off the left of the screen
			SetPosition(0.99f + (posX - boundingBox[0]), posY);
		} else if (boundingBox[0] > 1) {
			//The asteroid has gone off the right of the screen
			SetPosition(-0.99f + (posX - boundingBox[2]), posY);
		} else if (boundingBox[3] < -1) {
			//The asteroid has gone off the bottom of the screen
			SetPosition(posX, 0.99f + (posY - boundingBox[1]));
		} else if (boundingBox[1] > 1) {
			//The asteroid has gone off the top of the screen
			SetPosition(posX, -0.99f + (posY - boundingBox[3]));
		} else {
			//Error I guess
		}
	}

	/* OLD METHOD
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
		SetPosition(newX, newY);

	}
	*/
}

void Asteroid::SetMoveVector(Vector2D* newVector) {
	moveVector = *newVector;
}

void Asteroid::Rotate(float angle) {
	for (int currentPoint = 0; currentPoint < 8; ++ currentPoint) {
		asteroidPoints[currentPoint].Rotate(angle,
			       			new Vector2D(0, 0));
	}
	RecalculateBB();
}

void Asteroid::SetPosition(float x, float y) {
	worldPosition.SetX(x);
	worldPosition.SetY(y);
}

void Asteroid::Render() {
	float tempX = worldPosition.GetX();
	float tempY = worldPosition.GetY();

	glBegin(GL_LINE_LOOP);
	for(int currentPoint = 0; currentPoint < 8; ++ currentPoint)
		glVertex2f(tempX + asteroidPoints[currentPoint].GetX(),
			tempY + asteroidPoints[currentPoint].GetY());
	glEnd();
	
	//Testing, draw Bounding Box
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(boundingBox[0], boundingBox[1]);
	glVertex2f(boundingBox[2], boundingBox[1]);
	glVertex2f(boundingBox[2], boundingBox[3]);
	glVertex2f(boundingBox[0], boundingBox[3]);
	glEnd();

}

bool Asteroid::SAT(GameObject* target) {
	//TODO
}

void Asteroid::Collide() {
	//TODO
}

void Asteroid::ApplyGravity(GameObject* target) {
	float newX, newY, posX, posY, targetX, targetY;

	posX = worldPosition.GetX();
	posY = worldPosition.GetY();
	targetX = target->GetPosition()->GetX();
	targetY = target->GetPosition()->GetY();

	newX = ((targetX - posX) * target->GetMass());
	newY = ((targetY - posY) * target->GetMass());

	moveVector.SetX(moveVector.GetX() + newX);
	moveVector.SetY(moveVector.GetY() + newY);
}

Vector2D* Asteroid::GetPosition() {
	return &worldPosition;
}

float Asteroid::GetMass() {
	return mass;
}

void Asteroid::SetMass(float mass) {
	this->mass = mass;
}

//This should ONLY be called if this object rotates.
//Movement of the box should be handled in the Update function
void Asteroid::RecalculateBB() {
	float maxX, minX, maxY, minY;

	maxX = worldPosition.GetX();
	minX = worldPosition.GetX();
	maxY = worldPosition.GetY();
	minY = worldPosition.GetY();
	
	float tempX = worldPosition.GetX();
	float tempY = worldPosition.GetY();
	
	Vector2D* currentPoint;

	for (int curPoint = 0; curPoint < 8; ++curPoint) {
		currentPoint = &asteroidPoints[curPoint];
		if (tempX + currentPoint->GetX() < minX)
		       minX = tempX + currentPoint->GetX();
		if (tempX + currentPoint->GetX() > maxX)
		       maxX = tempX + currentPoint->GetX();
		if (tempY + currentPoint->GetY() < minY)
		       minY = tempY + currentPoint->GetY();
		if (tempY + currentPoint->GetY() > maxY)
		       maxY = tempY + currentPoint->GetY();
	}

	boundingBox[0] = minX;
	boundingBox[2] = maxX;
	boundingBox[1] = minY;
	boundingBox[3] = maxY;

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

	//Generate the bounding box
	RecalculateBB();	
}
