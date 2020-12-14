#pragma once

#include "GameObject.h"
#include "CollisionBox.h"

class Cube : public GameObject
{
private:


public:
	Cube();
	Cube(Mesh* mesh_, Shader* shader_);
	Cube(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float maxSpeed_, Mesh* mesh_, Shader* shader_, CollisionBox* collisionBox_);
	~Cube();

	void Update(const float deltaTime);
	void Render();
	void OnDestroy();
	void ApplyForce(Vec3 force);

	/** Getters and setters **/
	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline Vec3 getPos() { return pos; }
	inline void setPos(const Vec3& pos_) { pos = pos_; }
	inline Shader* getShader() const { return shader; }
	inline CollisionBox* getCollisionBox() { return collisionBox; }

	Mesh* mesh;
	Shader* shader;
	CollisionBox* collisionBox;
};