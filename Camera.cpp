#include "Camera.h"
#include "MatrixMath.h"

Camera::Camera() {
	setProjectionMatrix(MatrixMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f));
	setViewMatrix(MatrixMath::lookAt(Vec3(0.0, 0.0, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f)));
	//view.print();

	rotate = MatrixMath::rotate(0.0, Vec3(0.0, 1.0, 0.0));
	translate = MatrixMath::translate(0.0, 0.0, -10.0);
	view = rotate.multiplyMat(translate);
}

Camera::~Camera() {}

bool Camera::OnCreate()
{
	return true;
}

void Camera::OnDestroy() {

}

void Camera::Update(const float deltaTime) {
}

void Camera::HandleEvents(const SDL_Event& event) {

}

void Camera::Render()
{

}