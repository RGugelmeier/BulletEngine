#ifndef GameObject_H
#define GameObject_H
#include "Vec3.h"

class GameObject {
private:

public:
	GameObject();
	GameObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_);
	~GameObject();
	void Update(const float deltaTime);
	void ApplyForce(Vec3 force);
	Vec3 GetPos();
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
};

#endif

