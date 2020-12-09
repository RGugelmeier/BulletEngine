#pragma once
#include <SDL.h>

#include "Vec3.h"
#include "Matrix4.h"
#include "GameObject.h"

class Camera
{
private:


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
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view; }
	inline void setProjectionMatrix(Matrix4 projection_) { projection = projection_; }
	inline void setViewMatrix(Matrix4 view_) { view = view_; }

	Camera();
	~Camera();
};

