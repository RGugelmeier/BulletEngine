#include "CollisionBox.h"

CollisionBox::CollisionBox() : isColliding(false)
{
	size.Zero();
}

CollisionBox::CollisionBox(Vec3 size_, Vec3 pos_) : isColliding(false)
{
	size = size_;
	pos = pos_;
}

CollisionBox::~CollisionBox() {}

void CollisionBox::CheckCollision(CollisionBox otherCollider)
{
	// TO-DO
	//Check collisions on all 6 sides of the box. The box's walls could potentially be stored in variables instead and test against those variables to clean up the code.
	if (pos.x + (size.x / 2) >= otherCollider.pos.x - (otherCollider.size.x / 2) &&
		pos.x - (size.x / 2) <= otherCollider.pos.x + (otherCollider.size.x / 2) &&
		pos.y + (size.y / 2) >= otherCollider.pos.y - (otherCollider.size.y / 2) &&
		pos.y - (size.y / 2) <= otherCollider.pos.y + (otherCollider.size.y / 2) &&
		pos.z + (size.z / 2) >= otherCollider.pos.z - (otherCollider.size.z / 2) &&
		pos.z - (size.z / 2) <= otherCollider.pos.z + (otherCollider.size.z / 2))
	{
		if (pos.x + (size.x / 2) >= otherCollider.pos.x - (otherCollider.size.x / 2) && pos.x + (size.x / 2) <= otherCollider.pos.x - (otherCollider.size.x / 2.1f))
		{
			rightCollision = true;
		}
		else if (pos.x - (size.x / 2) <= otherCollider.pos.x + (otherCollider.size.x / 2) && pos.x - (size.x / 2) >= otherCollider.pos.x + (otherCollider.size.x / 2.1f))
		{
			leftCollision = true;
		}
		else if (pos.y + (size.y / 2) >= otherCollider.pos.y - (otherCollider.size.y / 2) && pos.y + (size.y / 2) <= otherCollider.pos.y - (otherCollider.size.y / 2.1f))
		{
			topCollision = true;
		}
		else if (pos.y - (size.y / 2) <= otherCollider.pos.y + (otherCollider.size.y / 2))
		{
			bottomCollision = true;
		}
		else if (pos.z - (size.z / 2) <= otherCollider.pos.z + (otherCollider.size.z / 2) && pos.z - (size.z / 2) >= otherCollider.pos.z + (otherCollider.size.z / 2.1f))
		{
			frontCollision = true;
		}
		else if (pos.z + (size.z / 2) >= otherCollider.pos.z - (otherCollider.size.z / 2) && pos.z + (size.z / 2) <= otherCollider.pos.z - (otherCollider.size.z / 2.1f))
		{
			backCollision = true;
		}
	}

	else
	{
		rightCollision = false;
		leftCollision = false;
		topCollision = false;
		bottomCollision = false;
		frontCollision = false;
		backCollision = false;
	}
}