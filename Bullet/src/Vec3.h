#ifndef VEC3_H
#define VEC3_H
#define PI 3.141592
#define DEGREES_TO_RADIANS (PI / 180.0F)

#include <iostream>
#include <math.h>

using namespace std;

class Vec3
{
public:
	Vec3();
	Vec3(float x_, float y_, float z_);

	void Add(Vec3 b);

	void Subtract(Vec3 b);

	void ScalarMultiplication(float s);

	float Mag();

	void Normalize();

	float Dot(Vec3 b);

	void Lerp(Vec3 b, float t);

	void RotateZ(float angle);

	void Zero();

	Vec3 operator + (const Vec3& v) const;

	Vec3 operator - (const Vec3& v) const;

	Vec3 operator * (const float v) const;

	Vec3 Cross(const Vec3& a, const Vec3& b);

	inline operator const float* () const {
		return static_cast<const float*>(&x);
	}

	inline operator float* () {
		return static_cast<float*>(&x);
	}

	float x;
	float y;
	float z;
};

#endif