#include "Matrix4.h"

//Set all matrix4 values to the values given upon call.
Matrix4::Matrix4(float x0, float x1, float x2, float x3, float y0, float y1, float y2, float y3, float z0, float z1, float z2, float z3, float w0, float w1, float w2, float w3)
{
	matrix4[0] = x0; matrix4[4] = y0; matrix4[8] = z0; matrix4[12] = w0;
	matrix4[1] = x1; matrix4[5] = y1; matrix4[9] = z1; matrix4[13] = w1;
	matrix4[2] = x2; matrix4[6] = y2; matrix4[10] = z2; matrix4[14] = w2;
	matrix4[3] = x3; matrix4[7] = y3; matrix4[11] = z3; matrix4[15] = w3;
}

//Set all matrix values to 0 by default.
Matrix4::Matrix4()
{
	matrix4[0] = 0;   matrix4[4] = 0;   matrix4[8] = 0;   matrix4[12] = 0;
	matrix4[1] = 0;   matrix4[5] = 0;   matrix4[9] = 0;   matrix4[13] = 0;
	matrix4[2] = 0;   matrix4[6] = 0;   matrix4[10] = 0;  matrix4[14] = 0;
	matrix4[3] = 0;   matrix4[7] = 0;   matrix4[11] = 0;  matrix4[15] = 0;
}

//This multiplies two matrices together. To do this, multiply the first value in the first row of the first matrix, with the first value in the first column of the second matrix,
//then multiply the second value in the first row of the first matrix with the second value in the first column of the second matrix and so on...
Matrix4 Matrix4::multiplyMat(Matrix4 otherMat)
{
	Matrix4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix4[i * 4 + j] = (matrix4[0 * 4 + j] * otherMat.matrix4[i * 4 + 0]) + (matrix4[1 * 4 + j] * otherMat.matrix4[i * 4 + 1]) + (matrix4[2 * 4 + j] * otherMat.matrix4[i * 4 + 2]) + (matrix4[3 * 4 + j] * otherMat.matrix4[i * 4 + 3]);
		}
	}
	return result;
}

//Multiplying a matrix4 by a vector4. To do this, multiply each number in the matrix's row by the first number in the vector and so on.
Vec4 Matrix4::multiplyVec4(Vec4 otherVec4)
{
	float x = otherVec4.x * matrix4[0] + otherVec4.y * matrix4[4] + otherVec4.z * matrix4[8] + otherVec4.w * matrix4[12];
	float y = otherVec4.x * matrix4[1] + otherVec4.y * matrix4[5] + otherVec4.z * matrix4[9] + otherVec4.w * matrix4[13];
	float z = otherVec4.x * matrix4[2] + otherVec4.y * matrix4[6] + otherVec4.z * matrix4[10] + otherVec4.w * matrix4[14];
	float w = otherVec4.x * matrix4[3] + otherVec4.y * matrix4[7] + otherVec4.z * matrix4[11] + otherVec4.w * matrix4[15];
	return Vec4(x, y, z, w);
}

//Multiplying a matrix4 by a vector3. To do this do the same as Vec4 multiplication but set the w values to 1.
Vec3 Matrix4::multiplyVec3(Vec3 otherVec3)
{
	float x = otherVec3.x * matrix4[0] + otherVec3.y * matrix4[4] + otherVec3.z * matrix4[8] + 1.0f * matrix4[12];
	float y = otherVec3.x * matrix4[1] + otherVec3.y * matrix4[5] + otherVec3.z * matrix4[9] + 1.0f * matrix4[13];
	float z = otherVec3.x * matrix4[2] + otherVec3.y * matrix4[6] + otherVec3.z * matrix4[10] + 1.0f * matrix4[14];
	float w = otherVec3.x * matrix4[3] + otherVec3.y * matrix4[7] + otherVec3.z * matrix4[11] + 1.0f * matrix4[15];
	return Vec3(x, y, z);
}

//Multiplying the matrix4 by a scalar. To do this, just multiply each number in the matrix by the scalar.
Matrix4 Matrix4::multiplyScalar(int scalar)
{
	matrix4[0] *= scalar;    matrix4[4] *= scalar;   matrix4[8] *= scalar;   matrix4[12] *= scalar;
	matrix4[1] *= scalar;    matrix4[5] *= scalar;   matrix4[9] *= scalar;   matrix4[13] *= scalar;
	matrix4[2] *= scalar;    matrix4[6] *= scalar;   matrix4[10] *= scalar;   matrix4[14] *= scalar;
	matrix4[3] *= scalar;    matrix4[7] *= scalar;   matrix4[11] *= scalar;   matrix4[15] *= scalar;

	return Matrix4();
}

//Adding one matrix with another. To do this just add all the matrix values together.
Matrix4 Matrix4::addMat(Matrix4 otherMat)
{
	matrix4[0] += otherMat.matrix4[0];   matrix4[4] += otherMat.matrix4[4];   matrix4[8] += otherMat.matrix4[8];   matrix4[12] += otherMat.matrix4[12];
	matrix4[1] += otherMat.matrix4[1];	 matrix4[5] += otherMat.matrix4[5];	  matrix4[9] += otherMat.matrix4[9];   matrix4[13] += otherMat.matrix4[13];
	matrix4[2] += otherMat.matrix4[2];	 matrix4[6] += otherMat.matrix4[6];	  matrix4[10] += otherMat.matrix4[10];   matrix4[14] += otherMat.matrix4[14];
	matrix4[3] += otherMat.matrix4[3];	 matrix4[7] += otherMat.matrix4[7];	  matrix4[11] += otherMat.matrix4[11];   matrix4[15] += otherMat.matrix4[15];

	return Matrix4();
}

//Subrtacting one matrix with another. To do this subtract all the matrix values with each other.
Matrix4 Matrix4::subtractMat(Matrix4 otherMat)
{
	matrix4[0] -= otherMat.matrix4[0];   matrix4[4] -= otherMat.matrix4[4];   matrix4[8] -= otherMat.matrix4[8];   matrix4[12] -= otherMat.matrix4[12];
	matrix4[1] -= otherMat.matrix4[1];	 matrix4[5] -= otherMat.matrix4[5];	  matrix4[9] -= otherMat.matrix4[9];   matrix4[13] -= otherMat.matrix4[13];
	matrix4[2] -= otherMat.matrix4[2];	 matrix4[6] -= otherMat.matrix4[6];	  matrix4[10] -= otherMat.matrix4[10];   matrix4[14] -= otherMat.matrix4[14];
	matrix4[3] -= otherMat.matrix4[3];	 matrix4[7] -= otherMat.matrix4[7];	  matrix4[11] -= otherMat.matrix4[11];   matrix4[15] -= otherMat.matrix4[15];

	return Matrix4();
}