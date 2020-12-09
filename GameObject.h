#ifndef GameObject_H
#define GameObject_H
#include "Vec3.h"
#include "Mesh.h"
#include "Shader.h"
#include "Matrix4.h"

class GameObject {
private:
	
	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;
	Mesh* mesh;
	Shader* shader;

public:
	GameObject(Mesh* mesh_, Shader* shader_);
	GameObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, Mesh *mesh_, Shader* shader_);
	~GameObject();

	void Update(const float deltaTime);
	void Render();
	void OnDestroy();
	void ApplyForce(Vec3 force);
	Vec3 GetPos();

	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;

	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
	inline void setPos(const Vec3& pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; } 
};

#endif

