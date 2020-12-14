#pragma once

#include "GameObject.h"

class CollisionBox : public GameObject
{
public:

	CollisionBox();
	CollisionBox(Vec3 size_, Vec3 pos_);
	~CollisionBox();

	bool isColliding;
	bool rightCollision, leftCollision, bottomCollision, topCollision, frontCollision, backCollision;

	Vec3 size;

	void CheckCollision(CollisionBox otherCollider);

	float standingPoint;
private:
};