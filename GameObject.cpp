#include "GameObject.h"

#include "MatrixMath.h"

/* GameObject Constructor
	Sets the GameObject's components to 0. Also gets the model and normal matrix IDs from the shader for rendering. */
GameObject::GameObject(Mesh* mesh_, Shader* shader_) : mesh(mesh_), shader(shader_) {
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	vel.x = 0;
	vel.y = 0;
	vel.z = 0;
	accel.x = 0;
	accel.y = 0;
	accel.z = 0;
	mass = 0;

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

/* GameObject Constructor
	Set the GameObject's components to the parameters supplied. Also gets the model and normal matrix IDs from the shader for rendering. */
GameObject::GameObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, Mesh* mesh_, Shader* shader_) : mesh(mesh_), shader(shader_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;
	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;
	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;
	mass = mass_;

	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
}

/* GameObject Deconstructor */
GameObject::~GameObject() {
}

/* Update function
	Updates the GameObject's position using it's current velocity and acceleration */
void GameObject::Update(const float deltaTime) {
	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	vel.x += accel.x * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	vel.y += accel.y * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * accel.z * deltaTime * deltaTime;
	vel.z += accel.z * deltaTime;
}

void GameObject::Render()
{
	Matrix3 normalMatrix = MatrixMath::transpose(MatrixMath::inverse(modelMatrix));

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix.matrix4);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix.matrix3);
	
	mesh->Render();
}

void GameObject::OnDestroy()
{
}

/* Apply Force function
	Calculates the GameObject's new acceleration with the given applied force and it's mass */
void GameObject::ApplyForce(Vec3 force) {
	accel.x = force.x / mass;
	accel.y = force.y / mass;
	accel.z = force.z / mass;
}

/* Get Position Function
	Gets the GameObject's current position */
Vec3 GameObject::GetPos() {
	return pos;
}