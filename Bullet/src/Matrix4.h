#pragma once
#include "Vec3.h"
#include "Vec4.h"
class Matrix4
{
public:
	//The matrix array. Needs to be public so matrix3s can get to it.
	float matrix4[16];

	//Set up the matrix manually.
	Matrix4(float x0, float x1, float x2, float x3,
			float y0, float y1, float y2, float y3,
			float z0, float z1, float z2, float z3, 
			float w0, float w1, float w2, float w3);

	//Default intializer. Sets all values to 0.
	Matrix4();

	Matrix4 multiplyMat(Matrix4 otherMat);

	Vec3 multiplyVec3(Vec3 otherVec3);

	Vec4 multiplyVec4(Vec4 otherVec4);

	Matrix4 multiplyScalar(int scalar);

	Matrix4 addMat(Matrix4 otherMat);

	Matrix4 subtractMat(Matrix4 otherMat);
};