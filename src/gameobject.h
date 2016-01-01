//*****************************************************************************
//An abstract class that all game objects must inherit from
//
//Samuel Kinnett, 2015
//*****************************************************************************

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "vector2D.h"

class GameObject {

	public:		
		virtual void Update() = 0;
		virtual void SetMoveVector(Vector2D*) = 0;
		virtual void SetPosition(float, float) = 0;
		virtual void Rotate(float) = 0;
		virtual void Render() = 0;
		virtual bool AABB(GameObject*) = 0;
		//Axis Alligned Bounding Box collision detection
		virtual bool SAT(GameObject*) = 0;
		//Separating Axis Theorem collision detection
		virtual void Collide() = 0;
		virtual void ApplyGravity(GameObject*) = 0;

		virtual Vector2D* GetPosition() = 0;
		virtual float GetMass() = 0;
		virtual void SetMass(float) = 0;

		bool gravAffected = false;	//Is the object affected by gravity?
};

#endif
