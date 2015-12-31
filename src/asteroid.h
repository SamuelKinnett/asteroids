//*****************************************************************************
//A class describing an asteroid
//
//Samuel Kinnett, 2015
//*****************************************************************************

#ifndef ASTEROID_H
#define ASTEROID_H

#include "gameobject.h"
#ifdef _WIN32
#include "Windows.h"
#endif
#include "GL/gl.h"

class Asteroid : GameObject {

	public:
		Asteroid();
		~Asteroid();

		virtual void Update();
		virtual void Move(float x, float y);
		virtual void Render();
		virtual bool AABB(GameObject*);
		virtual bool SAT(GameObject*);
		virtual void Collide();

	private:
		
		Vector2D worldPosition;
		float BoundingBox[4];
		void RecalculateBB();
		void GenerateAsteroid();
		
		int size;
		Vector2D asteroidPoints[8];

};

#endif
