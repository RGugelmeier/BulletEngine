#pragma once
#include "Matrix4.h"

class Matrix3
{
private:

public:
	float matrix3[9];
	Matrix3 multiplyMat(Matrix3 otherMat);

	Matrix3(float x0, float x1, float x2,
			float z0, float z1, float z2,
			float y0, float y1, float y2);

	Matrix3(Matrix4 mat4);

	Matrix3();
};			
