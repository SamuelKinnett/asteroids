//*****************************************************************************
//An abstract class that all game objects must inherit from
//
//Samuel Kinnett, 2015
//*****************************************************************************

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "renderable.h"
#include "vector2D.h"

class GameObject : Renderable {

	public:		
		virtual void Update() = 0;
		virtual void Move(float x, float y) = 0;
		virtual void Render() = 0;
		virtual bool AABB(GameObject*) = 0;
		//Axis Alligned Bounding Box collision detection
		virtual bool SAT(GameObject*) = 0;
		//Separating Axis Theorem collision detection
		virtual void collide() = 0;
};

#endif
