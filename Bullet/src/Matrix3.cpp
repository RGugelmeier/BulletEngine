#include "Matrix3.h"

//This multiplies two matrices together. To do this, multiply the first value in the first row of the first matrix, with the first value in the first column of the second matrix,
//then multiply the second value in the first row of the first matrix with the second value in the first column of the second matrix and so on...
Matrix3 Matrix3::multiplyMat(Matrix3 otherMat)
{
	Matrix3 result;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.matrix3[i * 3 + j] = (matrix3[0 * 3 + j] * otherMat.matrix3[i * 3 + 0]) + (matrix3[1 * 3 + j] * otherMat.matrix3[i * 3 + 1]) + (matrix3[2 * 3 + j] * otherMat.matrix3[i * 3 + 2]);
		}
	}
	return result;
}

//Set all matrix4 values to the values given upon call.
Matrix3::Matrix3(float x0, float x1, float x2, float z0, float z1, float z2, float y0, float y1, float y2)
{
	matrix3[0] = x0; matrix3[3] = y0; matrix3[6] = z0; 
	matrix3[1] = x1; matrix3[4] = y1; matrix3[7] = z1; 
	matrix3[2] = x2; matrix3[5] = y2; matrix3[8] = z2;
}

//Takes the top 3x3 from the matrix4 and applies it to the matrix3.
Matrix3::Matrix3(Matrix4 mat4)
{
	matrix3[0] = mat4.matrix4[0];	matrix3[3] = mat4.matrix4[3];	matrix3[6] = mat4.matrix4[6];
	matrix3[1] = mat4.matrix4[1];	matrix3[4] = mat4.matrix4[4];	matrix3[7] = mat4.matrix4[7];
	matrix3[2] = mat4.matrix4[2];	matrix3[5] = mat4.matrix4[5];	matrix3[8] = mat4.matrix4[8];
}

//Set all matrix values to 0 by default.
Matrix3::Matrix3()
{
	matrix3[0] = 0; matrix3[3] = 0; matrix3[6] = 0;
	matrix3[1] = 0; matrix3[4] = 0; matrix3[7] = 0;
	matrix3[2] = 0; matrix3[5] = 0; matrix3[8] = 0;
}
