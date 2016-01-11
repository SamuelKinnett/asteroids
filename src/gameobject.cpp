#include "gameobject.h"

bool GameObject::AABB(GameObject* target) {
	float* targetBB = target->GetBB();

	//Check if separate
	if (this->boundingBox[2] < targetBB[0]
		|| targetBB[2] < this->boundingBox[0]
		|| this->boundingBox[3] > targetBB[1]
		|| targetBB[3] > this->boundingBox[1])
		return false;

	return true;
}

float * GameObject::GetBB() {
	return this->boundingBox;
}
