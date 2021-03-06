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
		virtual bool SAT(GameObject*);
		virtual void Collide();
		virtual void ApplyGravity(GameObject*);

		virtual Vector2D* GetPosition();
		virtual float GetMass();
		virtual void SetMass(float);

		void RecalculateBB();
		void BeginSmoothRotation(float);
		void StopSmoothRotation();
		void BeginAcceleration(float);
		void StopAcceleration();

		void SetVelocity(float);

	private:

		Vector2D shipPoints[4];
		Vector2D worldPosition;
		Vector2D moveVector;
		float mass;
		float currentRotation;
		float currentRotationAmount;
		bool rotating;

		float currentVelocity;
		float acceleration;
		float maximumVelocity;
		float deceleration;
		bool moving;	//As in, is the player holding down the 
				// move key
};

#endif
