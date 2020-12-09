#include "MatrixMath.h"

Matrix4 MatrixMath::rotate(float degrees, float x, float y, float z)
{
	float cosAng, sinAng, cosM;
	Vec3 rotAxis(x, y, z);
	rotAxis.Normalize();
	degrees *= DEGREES_TO_RADIANS;
	cosAng = cos(degrees);
	sinAng = sin(degrees);
	cosM = (1.0f - cosAng);

	Matrix4 mat4;

	mat4.matrix4[0] = (rotAxis.x * rotAxis.y * cosM) + cosAng;
	mat4.matrix4[1] = (rotAxis.x * rotAxis.y * cosM) + (rotAxis.z * sinAng);
	mat4.matrix4[2] = (rotAxis.x * rotAxis.z * cosM) - (rotAxis.y * sinAng);
	mat4.matrix4[3] = 0.0;
	mat4.matrix4[4] = (rotAxis.x * rotAxis.y * cosM) - (rotAxis.z * sinAng);
	mat4.matrix4[5] = (rotAxis.y * rotAxis.y * cosM) + cosAng;
	mat4.matrix4[6] = (rotAxis.y * rotAxis.z * cosM) + (rotAxis.x * sinAng);
	mat4.matrix4[7] = 0.0;
	mat4.matrix4[8] = (rotAxis.x * rotAxis.z * cosM) + (rotAxis.y * sinAng);
	mat4.matrix4[9] = (rotAxis.y * rotAxis.z * cosM) - (rotAxis.x * sinAng);
	mat4.matrix4[10] = (rotAxis.z * rotAxis.z * cosM) + cosAng;
	mat4.matrix4[11] = 0.0;
	mat4.matrix4[12] = 0.0;
	mat4.matrix4[13] = 0.0;
	mat4.matrix4[14] = 0.0;
	mat4.matrix4[15] = 1.0;
	return mat4;
}

//Overload rotate to use a Vec3
Matrix4 MatrixMath::rotate(const float degrees, const Vec3& axis)
{
	return MatrixMath::rotate(degrees, axis.x, axis.y, axis.z);
}

//Translate the matrix4
Matrix4 MatrixMath::translate(float x_, float y_, float z_)
{
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 1.0f, 0.0f,
				   x_, y_, z_, 1.0f);
}

//overload for translate if inputing a Vec3
Matrix4 MatrixMath::translate(const Vec3& translate_) {
	return MatrixMath::translate(translate_.x, translate_.y, translate_.z);
}

//Scales the matrix by the variables given.
Matrix4 MatrixMath::scale(float x_, float y_, float z_) {
	return Matrix4(x_, 0.0f, 0.0f, 0.0f,
				   0.0f, y_, 0.0f, 0.0f,
				   0.0f, 0.0f, z_, 0.0f,
				   0.0f, 0.0f, 0.0f, 1.0f);
}

//Overload for scale when given a Vec3
Matrix4 MatrixMath::scale(const Vec3& scale) {
	return MatrixMath::scale(scale.x, scale.y, scale.z);
}

Matrix4 MatrixMath::perspective(float fovy, float aspect, float zNear, float zFar)
{
	float cot = 1.0f / tan(fovy * 0.5f * DEGREES_TO_RADIANS);

	Matrix4 result(cot / aspect,  0.0f, 0.0f,									0.0f,
				   0.0f,		  cot , 0.0f,									0.0f,
				   0.0f,		  0.0f, (zNear + zFar) / (zNear - zFar),		-1.0f,
				   0.0f,		  0.0f, (2.0f * zNear * zFar) / (zNear - zFar),	0.0f);
	return result;
}

Matrix4 MatrixMath::viewportNDC(int width_, int height_)
{
	float minZ = 0.0f;
	float maxZ = 1.0f;

	Matrix4 m1 = scale(1.0f, -1.0f, 1.0f);
	Matrix4 m2 = scale(float(width_) / 2.0f, float(height_) / 2.0f, maxZ - minZ);
	Matrix4 m3 = translate(float(width_) / 2.0f, float(height_) / 2.0f, minZ);
	m3.multiplyMat(m2); m3.multiplyMat(m1);
	
	return m3;
}

Matrix4 MatrixMath::orthographic(float xMin_, float xMax_, float yMin_, float yMax_, float zMin_, float zMax_)
{
	Matrix4 m1 = MatrixMath::scale(2.0f / (xMax_ - xMin_), 2.0f / (yMax_ - yMin_), -2.0f / (zMax_ - zMin_));
	Matrix4 m2 = MatrixMath::translate(-(xMax_ + xMin_) / (xMax_ - xMin_), -(yMax_ + yMin_) / (yMax_ - yMin_), -(zMax_ + zMin_) / (zMax_ - zMin_));
	m2.multiplyMat(m1);

	return m2;
}

//This undoes orthographic
Matrix4 MatrixMath::unOrtho(const Matrix4& ortho)
{
	Matrix4 mat4;
	mat4.matrix4[0] = 1.0f / ortho.matrix4[0];
	mat4.matrix4[5] = 1.0f / ortho.matrix4[5];
	mat4.matrix4[10] = 1.0f / ortho.matrix4[10];
	mat4.matrix4[12] = -ortho.matrix4[12] * mat4.matrix4[0];
	mat4.matrix4[13] = -ortho.matrix4[13] * mat4.matrix4[5];
	mat4.matrix4[14] = -ortho.matrix4[14] * mat4.matrix4[10];
	mat4.matrix4[15] = 1.0f;
	return mat4;
}

Matrix4 MatrixMath::lookAt(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ)
{
	Vec3 at(atX, atY, atZ);
	Vec3 up(upX, upY, upZ);
	Vec3 eye(eyeX, eyeY, eyeZ);

	Matrix4 result;
	Vec3 forward;
	Vec3 side;
	Vec3 temp;

	temp = at - eye;
	temp.Normalize();
	forward = temp;
	up.Normalize();
	
	side.Cross(forward, up);
	side.Normalize();
	up.Cross(side, forward);

	result.matrix4[0] = side.x;		result.matrix4[4] = up.x;	result.matrix4[8] = -forward.x;		result.matrix4[12] = -side.Dot(eye);
	result.matrix4[1] = side.y;		result.matrix4[5] = up.y;	result.matrix4[9] = -forward.y;		result.matrix4[13] = -up.Dot(eye);
	result.matrix4[2] = side.z;		result.matrix4[6] = up.z;	result.matrix4[10] = -forward.z;	result.matrix4[14] = forward.Dot(eye);
	result.matrix4[3] = 0.0;		result.matrix4[7] = 0.0;	result.matrix4[11] = 0.0;			result.matrix4[15] = 1.0;

	return result;
}

//Overload for lookAt where you give three Vec3s instead of individual values.
Matrix4 MatrixMath::lookAt(const Vec3& eye, const Vec3& at, const Vec3& up)
{
	return lookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);
}

Matrix4 MatrixMath::transpose(const Matrix4& mat4)
{
	return Matrix4( mat4.matrix4[0], mat4.matrix4[4], mat4.matrix4[8], mat4.matrix4[12],
					mat4.matrix4[1], mat4.matrix4[5], mat4.matrix4[9], mat4.matrix4[13],
					mat4.matrix4[2], mat4.matrix4[6], mat4.matrix4[10], mat4.matrix4[14],
					mat4.matrix4[3], mat4.matrix4[7], mat4.matrix4[11], mat4.matrix4[15]);
}

Matrix4 MatrixMath::inverse(const Matrix4& mat4)
{
	Matrix4 inverseM;
	float determinate;

	inverseM.matrix4[0] = mat4.matrix4[5] * mat4.matrix4[10] * mat4.matrix4[15] - mat4.matrix4[5] * mat4.matrix4[11] * mat4.matrix4[14] - mat4.matrix4[9] * mat4.matrix4[6] * mat4.matrix4[15] + mat4.matrix4[9] * mat4.matrix4[7] * mat4.matrix4[14] + mat4.matrix4[13] * mat4.matrix4[6] * mat4.matrix4[11] - mat4.matrix4[13] * mat4.matrix4[7] * mat4.matrix4[10];
	inverseM.matrix4[1] = -mat4.matrix4[1] * mat4.matrix4[10] * mat4.matrix4[15] + mat4.matrix4[1] * mat4.matrix4[11] * mat4.matrix4[14] + mat4.matrix4[9] * mat4.matrix4[2] * mat4.matrix4[15] - mat4.matrix4[9] * mat4.matrix4[3] * mat4.matrix4[14] - mat4.matrix4[13] * mat4.matrix4[2] * mat4.matrix4[11] + mat4.matrix4[13] * mat4.matrix4[3] * mat4.matrix4[10];
	inverseM.matrix4[2] = mat4.matrix4[1] * mat4.matrix4[6] * mat4.matrix4[15] - mat4.matrix4[1] * mat4.matrix4[7] * mat4.matrix4[14] - mat4.matrix4[5] * mat4.matrix4[2] * mat4.matrix4[15] + mat4.matrix4[5] * mat4.matrix4[3] * mat4.matrix4[14] + mat4.matrix4[13] * mat4.matrix4[2] * mat4.matrix4[7] - mat4.matrix4[13] * mat4.matrix4[3] * mat4.matrix4[6];
	inverseM.matrix4[3] = -mat4.matrix4[1] * mat4.matrix4[6] * mat4.matrix4[11] + mat4.matrix4[1] * mat4.matrix4[7] * mat4.matrix4[10] + mat4.matrix4[5] * mat4.matrix4[2] * mat4.matrix4[11] - mat4.matrix4[5] * mat4.matrix4[3] * mat4.matrix4[10] - mat4.matrix4[9] * mat4.matrix4[2] * mat4.matrix4[7] + mat4.matrix4[9] * mat4.matrix4[3] * mat4.matrix4[6];
	inverseM.matrix4[4] = -mat4.matrix4[4] * mat4.matrix4[10] * mat4.matrix4[15] + mat4.matrix4[4] * mat4.matrix4[11] * mat4.matrix4[14] + mat4.matrix4[8] * mat4.matrix4[6] * mat4.matrix4[15] - mat4.matrix4[8] * mat4.matrix4[7] * mat4.matrix4[14] - mat4.matrix4[12] * mat4.matrix4[6] * mat4.matrix4[11] + mat4.matrix4[12] * mat4.matrix4[7] * mat4.matrix4[10];
	inverseM.matrix4[5] = mat4.matrix4[0] * mat4.matrix4[10] * mat4.matrix4[15] - mat4.matrix4[0] * mat4.matrix4[11] * mat4.matrix4[14] - mat4.matrix4[8] * mat4.matrix4[2] * mat4.matrix4[15] + mat4.matrix4[8] * mat4.matrix4[3] * mat4.matrix4[14] + mat4.matrix4[12] * mat4.matrix4[2] * mat4.matrix4[11] - mat4.matrix4[12] * mat4.matrix4[3] * mat4.matrix4[10];
	inverseM.matrix4[6] = -mat4.matrix4[0] * mat4.matrix4[6] * mat4.matrix4[15] + mat4.matrix4[0] * mat4.matrix4[7] * mat4.matrix4[14] + mat4.matrix4[4] * mat4.matrix4[2] * mat4.matrix4[15] - mat4.matrix4[4] * mat4.matrix4[3] * mat4.matrix4[14] - mat4.matrix4[12] * mat4.matrix4[2] * mat4.matrix4[7] + mat4.matrix4[12] * mat4.matrix4[3] * mat4.matrix4[6];
	inverseM.matrix4[7] = mat4.matrix4[0] * mat4.matrix4[6] * mat4.matrix4[11] - mat4.matrix4[0] * mat4.matrix4[7] * mat4.matrix4[10] - mat4.matrix4[4] * mat4.matrix4[2] * mat4.matrix4[11] + mat4.matrix4[4] * mat4.matrix4[3] * mat4.matrix4[10] + mat4.matrix4[8] * mat4.matrix4[2] * mat4.matrix4[7] - mat4.matrix4[8] * mat4.matrix4[3] * mat4.matrix4[6];
	inverseM.matrix4[8] = mat4.matrix4[4] * mat4.matrix4[9] * mat4.matrix4[15] - mat4.matrix4[4] * mat4.matrix4[11] * mat4.matrix4[13] - mat4.matrix4[8] * mat4.matrix4[5] * mat4.matrix4[15] + mat4.matrix4[8] * mat4.matrix4[7] * mat4.matrix4[13] + mat4.matrix4[12] * mat4.matrix4[5] * mat4.matrix4[11] - mat4.matrix4[12] * mat4.matrix4[7] * mat4.matrix4[9];
	inverseM.matrix4[9] = -mat4.matrix4[0] * mat4.matrix4[9] * mat4.matrix4[15] + mat4.matrix4[0] * mat4.matrix4[11] * mat4.matrix4[13] + mat4.matrix4[8] * mat4.matrix4[1] * mat4.matrix4[15] - mat4.matrix4[8] * mat4.matrix4[3] * mat4.matrix4[13] - mat4.matrix4[12] * mat4.matrix4[1] * mat4.matrix4[11] + mat4.matrix4[12] * mat4.matrix4[3] * mat4.matrix4[9];
	inverseM.matrix4[10] = mat4.matrix4[0] * mat4.matrix4[5] * mat4.matrix4[15] - mat4.matrix4[0] * mat4.matrix4[7] * mat4.matrix4[13] - mat4.matrix4[4] * mat4.matrix4[1] * mat4.matrix4[15] + mat4.matrix4[4] * mat4.matrix4[3] * mat4.matrix4[13] + mat4.matrix4[12] * mat4.matrix4[1] * mat4.matrix4[7] - mat4.matrix4[12] * mat4.matrix4[3] * mat4.matrix4[5];
	inverseM.matrix4[11] = -mat4.matrix4[0] * mat4.matrix4[5] * mat4.matrix4[11] + mat4.matrix4[0] * mat4.matrix4[7] * mat4.matrix4[9] + mat4.matrix4[4] * mat4.matrix4[1] * mat4.matrix4[11] - mat4.matrix4[4] * mat4.matrix4[3] * mat4.matrix4[9] - mat4.matrix4[8] * mat4.matrix4[1] * mat4.matrix4[7] + mat4.matrix4[8] * mat4.matrix4[3] * mat4.matrix4[5];
	inverseM.matrix4[12] = -mat4.matrix4[4] * mat4.matrix4[9] * mat4.matrix4[14] + mat4.matrix4[4] * mat4.matrix4[10] * mat4.matrix4[13] + mat4.matrix4[8] * mat4.matrix4[5] * mat4.matrix4[14] - mat4.matrix4[8] * mat4.matrix4[6] * mat4.matrix4[13] - mat4.matrix4[12] * mat4.matrix4[5] * mat4.matrix4[10] + mat4.matrix4[12] * mat4.matrix4[6] * mat4.matrix4[9];
	inverseM.matrix4[13] = mat4.matrix4[0] * mat4.matrix4[9] * mat4.matrix4[14] - mat4.matrix4[0] * mat4.matrix4[10] * mat4.matrix4[13] - mat4.matrix4[8] * mat4.matrix4[1] * mat4.matrix4[14] + mat4.matrix4[8] * mat4.matrix4[2] * mat4.matrix4[13] + mat4.matrix4[12] * mat4.matrix4[1] * mat4.matrix4[10] - mat4.matrix4[12] * mat4.matrix4[2] * mat4.matrix4[9];
	inverseM.matrix4[14] = -mat4.matrix4[0] * mat4.matrix4[5] * mat4.matrix4[14] + mat4.matrix4[0] * mat4.matrix4[6] * mat4.matrix4[13] + mat4.matrix4[4] * mat4.matrix4[1] * mat4.matrix4[14] - mat4.matrix4[4] * mat4.matrix4[2] * mat4.matrix4[13] - mat4.matrix4[12] * mat4.matrix4[1] * mat4.matrix4[6] + mat4.matrix4[12] * mat4.matrix4[2] * mat4.matrix4[5];
	inverseM.matrix4[15] = mat4.matrix4[0] * mat4.matrix4[5] * mat4.matrix4[10] - mat4.matrix4[0] * mat4.matrix4[6] * mat4.matrix4[9] - mat4.matrix4[4] * mat4.matrix4[1] * mat4.matrix4[10] + mat4.matrix4[4] * mat4.matrix4[2] * mat4.matrix4[9] + mat4.matrix4[8] * mat4.matrix4[1] * mat4.matrix4[6] - mat4.matrix4[8] * mat4.matrix4[2] * mat4.matrix4[5];

	determinate = mat4.matrix4[0] * inverseM.matrix4[0] + mat4.matrix4[1] * inverseM.matrix4[4] + mat4.matrix4[2] * inverseM.matrix4[8] + mat4.matrix4[3] * inverseM.matrix4[12];

#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
	if (fabs(determinate) < 1.0e-7f) {
		std::string errorMsg("Divide by nearly zero in MMath::inverse!");
		throw errorMsg;
	}
#endif

	determinate = 1.0f / determinate;
	for (int i = 0; i < 16; i++) {
		inverseM.matrix4[i] *= determinate;
	}
	return inverseM;
}

