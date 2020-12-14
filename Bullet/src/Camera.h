#pragma once
#include <SDL.h>

#include "Vec3.h"
#include "Matrix4.h"
#include "GameObject.h"

class Camera
{
private:
	float maxSpeed, maxRotateSpeed;

public:
	Matrix4 projection;
	Matrix4 rotate;
	Matrix4 translate;
	Matrix4 view;

	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime);
	void HandleEvents(const SDL_Event& event);
	void Render();

	void ApplyForce(Vec3 force);
	void ApplyTorque(float torque);

	void StopMoving();

	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view; }
	inline void setProjectionMatrix(Matrix4 projection_) { projection = projection_; }
	inline void setViewMatrix(Matrix4 view_) { view = view_; }

	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	Vec3 pos, vel, accel;
	float rotationalInertia, angle, angularVel, angularAcc;
	bool isMoving, isRotating;

	Camera();
	~Camera();
};

