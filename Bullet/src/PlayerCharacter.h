#pragma once

#include "CollisionBox.h"
#include "GameObject.h"
#include "Camera.h"

//This class is to be used as the player character. There are two overrides, one for third person and one for first person. This class's update will be called in the game loop in "Run()" in the SceneManager.

class PlayerCharacter
{
public:
	enum GAME_TYPE{ FIRST_PERSON, THIRD_PERSON, TOP_DOWN };

	PlayerCharacter(Mesh* mesh_, Shader* shader_, int gameType_, Vec3 pos_, Vec3 vel_, Vec3 accel_, CollisionBox* collisionBox_, float mass_, float maxSpeed_, float rotationalInertia_, float angle_, float angularVel_, float angularAcc_, float maxRotateSpeed_);
	PlayerCharacter(Mesh* mesh_, Shader* shader_, int gameType_);
	~PlayerCharacter();

	void Update(const float deltaTime);
	void Render();
	void OnDestroy();
	void HandleEvents(SDL_Event& event);

	void ApplyForce(Vec3 force);
	void ApplyTorque(float torque);

	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline Vec3 getPos() { return pos; }
	inline void setPos(const Vec3& pos_) { pos = pos_; }
	inline Shader* getShader() const { return shader; }

	void StopMoving();

	int gameType;

	Vec3 pos, vel, accel;
	float mass, rotationalInertia, angle, angularVel, angularAcc;
	bool isMoving, isRotating, isJumping;
	bool moveRight, moveLeft, moveForward, moveBack;
	bool canJump;
	CollisionBox* collisionBox;

	float rotateDeg = 0.0f;
	
	bool canMoveRight;
private:
	SDL_Event sdlEvent;

	float maxSpeed, maxRotateSpeed;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;

	Mesh* mesh;
	Shader* shader;
	Vec3 futurePos;

	bool applyGravity;
};