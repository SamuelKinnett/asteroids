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
#include <ctime>

class Asteroid : public GameObject {

	public:
		Asteroid(float x = 0.0f, float y = 0.0f);
		~Asteroid();

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

	private:
		
		Vector2D worldPosition;
		Vector2D moveVector;
		float rotationAmount;
		void RecalculateBB();
		void GenerateAsteroid();
		
		int size;
		float mass;
		Vector2D asteroidPoints[8];

};

#endif
