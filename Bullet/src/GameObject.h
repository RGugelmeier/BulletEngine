#ifndef GameObject_H
#define GameObject_H
#include "Vec3.h"
#include "Mesh.h"
#include "Shader.h"
#include "Matrix4.h"

#include <SDL.h>

class GameObject {
private:
	

public:
	GameObject();
	GameObject(Mesh* mesh_, Shader* shader_);
	GameObject(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float maxSpeed_, Mesh *mesh_, Shader* shader_);
	~GameObject();

	void AddTag(string tag);
	bool HasTag(string tag);
	void Update(const float deltaTime);
	void Render();
	void OnDestroy();
	void ApplyForce(Vec3 force);
	void HandleEvents(const SDL_Event& event);
	void StopMoving();
	Vec3 GetPos();

	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
	inline void setPos(const Vec3& pos_) { pos = pos_; }
	inline Vec3 getPos() { return pos; } 
	
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;

	// TO-DO
	// FINISH TAG FUNCTION TO GAME OBJECTS
	list<string> tags;

	Mesh* mesh;
	Shader* shader;
	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;
};

#endif

