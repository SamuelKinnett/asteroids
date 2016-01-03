#include "player.h"

Player::Player() {
	this->worldPosition.SetX(0);
	this->worldPosition.SetY(0);

	//Construct the player graphic
	this->shipPoints[0].SetX(-0.01f);
	this->shipPoints[0].SetY(-0.02f);
	this->shipPoints[1].SetX(0.0f);
	this->shipPoints[1].SetY(0.0f);
	this->shipPoints[2].SetX(0.01f);
	this->shipPoints[2].SetY(-0.02f);
	this->shipPoints[3].SetX(0);
	this->shipPoints[3].SetY(0.02f);

	//Set the movement variables
	this->acceleration = 0.004f;
	this->deceleration = 0.001f;
	this->currentRotation = 0;
}

Player::~Player() {

}

void Player::Update() {
	
	float posX = this->worldPosition.GetX();
	float posY = this->worldPosition.GetY();

	//Accelerate / decelerate as necessarry
	
	if (this->moving) {
		if (this->currentVelocity + this->acceleration  < 
				this->maximumVelocity)
			this->currentVelocity += this->acceleration;
		else
			this->currentVelocity = this->maximumVelocity;
	} else {
		if (this->currentVelocity - this->deceleration > 0)
			this->currentVelocity -= this->deceleration;	
		else
			this->currentVelocity = 0;
	}

	if (this->rotating) {
		this->Rotate(currentRotationAmount);
	} else {

	}
	
	//Update the moveVector
	
	this->moveVector.SetX(0);
	this->moveVector.SetY(this->currentVelocity);
	this->moveVector.Rotate(this->currentRotation, new Vector2D(0, 0));

	//Move the player according to the movement vector
	posX += this->moveVector.GetX();
	posY += this->moveVector.GetY();
	this->SetPosition(posX, posY);

	//Handle wrapping around the screen
	
	bool offScreen = true;

	for (int i = 0; i < 4; ++i) {
		float pointX = this->shipPoints[i].GetX();
		float pointY = this->shipPoints[i].GetY();

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
		this->SetPosition(newX, newY);
	}

}

void Player::SetMoveVector(Vector2D* newVector) {
	
	this->moveVector = *newVector;
}

void Player::SetPosition(float x, float y) {
	
	this->worldPosition.SetX(x);
	this->worldPosition.SetY(y);
}

void Player::SetVelocity(float velocity) {
	
	this->currentVelocity = velocity;
}

void Player::BeginSmoothRotation(float angle) {
	
	this->rotating = true;
	this->currentRotationAmount = angle;
}

void Player::StopSmoothRotation() {

	this->rotating = false;
}

void Player::BeginAcceleration(float velocity) {

	this->moving = true;
	this->maximumVelocity = velocity;
}

void Player::StopAcceleration() {
	
	this->moving = false;
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
		this->shipPoints[i].Rotate(angle, new Vector2D(0.0f, 0.0f));
	}

	//Rotate the movement vector
	//this->moveVector.Rotate(angle, new Vector2D(0.0f, 0.0f));	
}

void Player::Render() {
	float tempX = this->worldPosition.GetX();
	float tempY = this->worldPosition.GetY();

	glBegin(GL_LINE_LOOP);
	for (int currentPoint = 0; currentPoint < 4; ++ currentPoint)
		glVertex2f(tempX + this->shipPoints[currentPoint].GetX(),
			tempY + this->shipPoints[currentPoint].GetY());
	glEnd();

}

bool Player::AABB(GameObject* target) {

}

bool Player::SAT(GameObject* target) {

}

void Player::Collide() {

}

void Player::ApplyGravity(GameObject* target) {
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

Vector2D* Player::GetPosition() {
	return &this->worldPosition;
}

float Player::GetMass() {
	return this->mass;
}

void Player::SetMass(float mass) {
	this->mass = mass;
}
