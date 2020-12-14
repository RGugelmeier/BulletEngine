#include "Camera.h"
#include "MatrixMath.h"

Camera::Camera() {
	//Set the matrices to show the correct thing. Then rotates, translates, and sets the view to where it wants to look at.
	setProjectionMatrix(MatrixMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f));
	setViewMatrix(MatrixMath::lookAt(pos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
	rotate = MatrixMath::rotate(0.0, Vec3(0.0, 1.0, 0.0));
	translate = MatrixMath::translate(0.0, 0.0, 0.0);
	view = rotate.multiplyMat(translate);

	pos = Vec3(0.0f, -1.5f, 0.0f);
	vel = Vec3(0.0f, 0.0f, 0.0f);
	accel = Vec3(0.0f, 0.0f, 0.0f);

	rotationalInertia = 1.0f;
	angularVel = 0.0f;
	angularAcc = 0.0f;
	angle = 0.0f;

	maxSpeed = 3.0f;
	maxRotateSpeed = 150.0f;
}

Camera::~Camera() {}

bool Camera::OnCreate()
{
	return true;
}

void Camera::OnDestroy() {

}

//Updates the camera's position and rotation.
void Camera::Update(const float deltaTime) {
	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	vel.x += accel.x * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	vel.y += accel.y * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * accel.z * deltaTime * deltaTime;
	vel.z += accel.z * deltaTime;

	angularVel += angularAcc * deltaTime;
	angle += angularVel * deltaTime + 0.5f * angularAcc * deltaTime * deltaTime;

	if (!isMoving)
	{
		StopMoving();
	}

	//Actual updates what you see.
	setProjectionMatrix(MatrixMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f));
	setViewMatrix(MatrixMath::lookAt(pos, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
	rotate = MatrixMath::rotate(angle, Vec3(0.0, 1.0, 0.0));
	translate = MatrixMath::translate(pos.x, pos.y, pos.z - 10.0f);
	view = rotate.multiplyMat(translate);
}

//Rotate the camera with q and e
void Camera::HandleEvents(const SDL_Event& event) {
	

	if (state[SDL_SCANCODE_Q])
	{
		angularVel = -300.0f;
	}
	else if (state[SDL_SCANCODE_E])
	{
		angularVel = 300.0f;
	}
	else
	{
		angularVel = 0.0f;
	}
}	
	
void Camera::ApplyForce(Vec3 force)
{	
	accel.x = force.x / 1;
	accel.y = force.y / 1;
	accel.z = force.z / 1;
}	
	
void Camera::ApplyTorque(float torque)
{	
	angularAcc = torque / rotationalInertia;
}	
	
void Camera::Render() {}
	
void Camera::StopMoving()
{	
	vel.Zero();
}	