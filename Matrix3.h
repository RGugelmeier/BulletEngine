#pragma once
class Matrix3
{
private:
	float matrix3[9];

public:
	Matrix3 multiplyMat(Matrix3 otherMat);

	Matrix3(float x0, float x1, float x2,
			float z0, float z1, float z2,
			float y0, float y1, float y2);

	Matrix3();
};			
