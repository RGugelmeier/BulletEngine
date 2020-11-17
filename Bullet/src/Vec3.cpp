#include "Vec3.h"

/* Vec3 Constructor
	Set the vector's x, y, and z components to 0 */
Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

/* Vec3 Constructor
	Set the vector's x, y, and z components to the parameters supplied */
Vec3::Vec3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

/* Add Member Function
	Adds the vector's x, y, and z components with the supplied vector's x, y, and z components */
void Vec3::Add(Vec3 b)
{
	x = x + b.x;
	y = y + b.y;
	z = z + b.z;
}

/* Subtract Member Function
	Subtracts the vector's x, y, and z components with the parameters supplied */
void Vec3::Subtract(Vec3 b)
{
	x = x - b.x;
	y = y - b.y;
	z = z - b.z;
}

/* ScalarMultiplication Member Function
	Multiplies the vector's x, y, and z components with the scalar provided */
void Vec3::ScalarMultiplication(float s)
{
	x = x * s;
	y = y * s;
	z = z * s;
}

/* Mag Member Funtion
	Calculates and returns the vector's magnitude */
float Vec3::Mag()
{
	float mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	return mag;
}

/* Normalize Member Function
	Normalizes the vector */
void Vec3::Normalize()
{
	float xtemp;
	float ytemp;
	float ztemp;

	xtemp = x / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
	ytemp = y / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
	ztemp = z / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));

	x = xtemp;
	y = ytemp;
	z = ztemp;
}

/* Dot Member Function
	Calculates and returns the scalar result for the dot product of the vector and vector applied */
float Vec3::Dot(Vec3 b)
{
	float dot = (x * b.x) + (y * b.y) + (z * b.z);
	return dot;
}

/* Lerp Member Function
	Calculates the lerp for the vector and vector supplied using unit interval t */
void Vec3::Lerp(Vec3 b, float t)
{
	float xtemp;
	float ytemp;
	float ztemp;

	xtemp = (1 - t) * x + (t * b.x);
	ytemp = (1 - t) * y + (t * b.y);
	ztemp = (1 - t) * z + (t * b.z);

	x = xtemp;
	y = ytemp;
	z = ztemp;
}

/* RotateZ Member Function
	Calculates the rotation for the vector */
void Vec3::RotateZ(float angle)
{
	float xtemp;
	float ytemp;

	xtemp = x * cos(angle) - y * sin(angle);
	ytemp = x * sin(angle) + y * cos(angle);

	x = xtemp;
	y = ytemp;
}

/* Overload the + symbol to add vectors */
Vec3 Vec3::operator+(const Vec3& v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

/* Overload the + symbol to subtract vectors */
Vec3 Vec3::operator-(const Vec3& v) const
{
	return Vec3(-x, -y, -z);
}

/* Overload the * symbol to multiply vectors */
Vec3 Vec3::operator*(const float v) const
{
	return Vec3(v * x, v * y, v * z);
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}