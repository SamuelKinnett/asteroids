//*****************************************************************************
//This class describes the player character
//
//Samuel Kinnett, 2016
//*****************************************************************************

#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#ifdef _WIN32
#define "Windows.h"
#endif
#include "GL/gl.h"

class Player : public GameObject {

	public:
		Player();
		~Player();
		
		virtual void Update();
		virtual void SetMoveVector(Vector2D*);
		virtual void SetPosition(float, float);
		virtual void Rotate(float);
		virtual void Render();
		virtual bool AABB(GameObject*);
		virtual bool SAT(GameObject*);
		virtual void Collide();
		virtual void ApplyGravity(GameObject*);

		virtual Vector2D* GetPosition();
		virtual float GetMass();
		virtual void SetMass(float);

		float currentVelocity;

	private:

		Vector2D shipPoints[3];
		Vector2D worldPosition;
		Vector2D moveVector;
		float mass;
		float currentRotation;

};

#endif
