#include "Vec4.h"

Vec4::Vec4(float x_, float y_, float z_, float w_)
{
}

Vec4::Vec4()
{
}

float Vec4::Mag()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return mag;
}

void Vec4::Normalize()
{
	float xtemp;
	float ytemp;
	float ztemp;
	float wtemp;

	xtemp = x / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
	ytemp = y / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
	ztemp = z / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
	wtemp = w / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));

	x = xtemp;
	y = ytemp;
	z = ztemp;
	w = wtemp;
}

float Vec4::Dot(Vec4 otherVec)
{
	float dot = (x * otherVec.x) + (y * otherVec.y) + (z * otherVec.z) + (w * otherVec.w);
	return dot;
}