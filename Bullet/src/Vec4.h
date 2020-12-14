#ifndef VEC4_H
#define VEC4_H

#include <iostream>
#include <math.h>

class Vec4
{
public:
	Vec4(float x_, float y_, float z_, float w_);
	Vec4();

	float x, y, z, w;

	float Mag();

	void Normalize();

	float Dot(Vec4 otherVec);
};
#endif