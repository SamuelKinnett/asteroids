#include "player.h"

Player::Player() {
	worldPosition.SetX(0);
	worldPosition.SetY(0);

	//Construct the player graphic
	shipPoints[0].SetX(-0.01f);
	shipPoints[0].SetY(-0.02f);
	shipPoints[1].SetX(0.0f);
	shipPoints[1].SetY(0.0f);
	shipPoints[2].SetX(0.01f);
	shipPoints[2].SetY(-0.02f);
	shipPoints[3].SetX(0);
	shipPoints[3].SetY(0.02f);

	//Set the movement variables
	acceleration = 0.004f;
	deceleration = 0.001f;
	currentRotation = 0;

	//Generate the bounding box
	RecalculateBB();
}

Player::~Player() {

}

void Player::Update() {
	
	float posX = worldPosition.GetX();
	float posY = worldPosition.GetY(); 

	//Accelerate / decelerate as necessarry
	
	if (moving) {
		if (currentVelocity + acceleration  < 
				maximumVelocity)
			currentVelocity += acceleration;
		else
			currentVelocity = maximumVelocity;
	} else {
		if (currentVelocity - deceleration > 0)
			currentVelocity -= deceleration;	
		else
			currentVelocity = 0;
	}

	if (rotating) {
		Rotate(currentRotationAmount);
	} else {

	}
	
	//Update the moveVector
	
	moveVector.SetX(0);
	moveVector.SetY(currentVelocity);
	moveVector.Rotate(currentRotation, new Vector2D(0, 0));

	//Move the player according to the movement vector
	posX += moveVector.GetX();
	posY += moveVector.GetY();
	SetPosition(posX, posY);

	//Move the bounding box
	boundingBox[0] += moveVector.GetX();
	boundingBox[2] += moveVector.GetX();
	boundingBox[1] += moveVector.GetY();
	boundingBox[3] += moveVector.GetY();

	//Handle wrapping around the screen
	
	bool offScreen = true;

	for (int i = 0; i < 4; ++i) {
		float pointX = shipPoints[i].GetX();
		float pointY = shipPoints[i].GetY();

		if (posX + pointX < 1.0f
			&& posX + pointX > -1.0f
			&& posY + pointY < 1.0f
			&& posY + pointY > -1.0f) {

			offScreen = false;
			break;
		}

	}

	if (offScreen) {
		float newX, newY;
		if (posX > 1.0f) {
			//The player has gone off the right of the screen
			newX = -0.99f;
			newY = posY;
		} else if (posX < -1.0f) {
			//The player has gone off the left of the screen
			newX = 0.99f;
			newY = posY;
		} else if (posY > 1.0f) {
			//The player has gone off the top of the screen
			newX = posX;
			newY = -0.99f;
		} else if (posY < -1.0f) {
			//The player has gone off the bottom of the screen
			newX = posX;
			newY = 0.99f;
		} else {
			//We shouldn't ever reach here!
			newX = 0;
			newY = 0;
		}
		SetPosition(newX, newY);
	}

}

void Player::SetMoveVector(Vector2D* newVector) {
	
	moveVector = *newVector;
}

void Player::SetPosition(float x, float y) {
	
	worldPosition.SetX(x);
	worldPosition.SetY(y);
}

void Player::SetVelocity(float velocity) {
	
	currentVelocity = velocity;
}

void Player::BeginSmoothRotation(float angle) {
	
	rotating = true;
	currentRotationAmount = angle;
}

void Player::StopSmoothRotation() {

	rotating = false;
}

void Player::BeginAcceleration(float velocity) {

	moving = true;
	maximumVelocity = velocity;
}

void Player::StopAcceleration() {
	
	moving = false;
}
void Player::Rotate(float angle) {

	//Update the currentRotation variable
	if (currentRotation + angle > 360)
		currentRotation = 0 + (angle - (360 - currentRotation));
	else if (currentRotation + angle < 0)
		currentRotation = 360 + (angle - currentRotation);
	else
		currentRotation += angle;

	//Update the ship's vector graphics
	for (int i = 0; i < 4; ++i) {
		shipPoints[i].Rotate(angle, new Vector2D(0.0f, 0.0f));
	}

	//Rotate the movement vector
	//this->moveVector.Rotate(angle, new Vector2D(0.0f, 0.0f));	
	
	//Recalculate the bounding box
	RecalculateBB();
}

void Player::Render() {
	float tempX = worldPosition.GetX();
	float tempY = worldPosition.GetY();

	glBegin(GL_LINE_LOOP);
	for (int currentPoint = 0; currentPoint < 4; ++ currentPoint)
		glVertex2f(tempX + shipPoints[currentPoint].GetX(),
			tempY + shipPoints[currentPoint].GetY());
	glEnd();


	//testing, draw the bounding box
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(boundingBox[0], boundingBox[1]);
	glVertex2f(boundingBox[2], boundingBox[1]);
	glVertex2f(boundingBox[2], boundingBox[3]);
	glVertex2f(boundingBox[0], boundingBox[3]);
	glEnd();

}

//recalculate the bounding box for AABB collision detection. 
void Player::RecalculateBB() {
	float maxX, minX, maxY, minY;

	maxX = worldPosition.GetX();
	minX = worldPosition.GetX();
	maxY = worldPosition.GetY();
	minY = worldPosition.GetY();

	float tempX = worldPosition.GetX();
	float tempY = worldPosition.GetY();

	Vector2D* currentPoint;

	for (int curPoint = 0; curPoint < 4; ++ curPoint) {
		currentPoint = &shipPoints[curPoint];

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

bool Player::SAT(GameObject* target) {

}

void Player::Collide() {

}

void Player::ApplyGravity(GameObject* target) {
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

Vector2D* Player::GetPosition() {
	return &worldPosition;
}

float Player::GetMass() {
	return mass;
}

void Player::SetMass(float mass) {
	this->mass = mass;
}
