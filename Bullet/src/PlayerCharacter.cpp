#include "PlayerCharacter.h"

#include "MatrixMath.h"

PlayerCharacter::PlayerCharacter(Mesh* mesh_, Shader* shader_, int gameType_, Vec3 pos_, Vec3 vel_, Vec3 accel_, CollisionBox* collisionBox_, float mass_, float maxSpeed_, float rotationalInertia_, float angle_, float angularVel_, float angularAcc_, float maxRotateSpeed_)
	: mesh(mesh_), shader(shader_), gameType(gameType_), isMoving(false), isRotating(false), collisionBox(collisionBox_), canMoveRight(true)
{
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");

	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;

	rotationalInertia = rotationalInertia_;
	angularVel = angularVel_;
	angularAcc = angularAcc_;
	angle = angle_;

	maxSpeed = maxSpeed_;
	maxRotateSpeed = maxRotateSpeed_;

	futurePos = Vec3(pos.x + 0.1f, pos.y + 0.1f, pos.z + 0.1f);

	moveRight = false;
	moveLeft = false;
	moveBack = false;
	moveForward = false;
	canJump = false;
}

PlayerCharacter::PlayerCharacter(Mesh* mesh_, Shader* shader_, int gameType_)
	: mesh(mesh_), shader(shader_), gameType(gameType_), isMoving(true), isRotating(false), canMoveRight(true)
{
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");

	/* Zero out the vectors as their base values. */
	pos.Zero();
	vel.Zero();
	accel.Zero();
	mass = 1.0f;

	rotationalInertia = 1.0f;
	angularVel = 0.0f;
	angularAcc = 0.0f;
	angle = 0.0f;

	applyGravity = true;

	collisionBox = new CollisionBox(Vec3(3.5f, 3.5f, 3.5f), pos);
	maxSpeed = 3.0f;
	maxRotateSpeed = 150.0f;

	moveRight = false;
	moveLeft = false;
	moveBack = false;
	moveForward = false;
	canJump = false;
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(const float deltaTime)
{
	
	pos.x += vel.x * deltaTime + 0.5f * accel.x * deltaTime * deltaTime;
	vel.x += accel.x * deltaTime;
	pos.y += vel.y * deltaTime + 0.5f * accel.y * deltaTime * deltaTime;
	vel.y += accel.y * deltaTime;
	pos.z += vel.z * deltaTime + 0.5f * accel.z * deltaTime * deltaTime;
	vel.z += accel.z * deltaTime;

	angularVel += angularAcc * deltaTime;
	angle += angularVel * deltaTime + 0.5f * angularAcc * deltaTime * deltaTime;

	//D
	if (moveRight == true)
	{
		if (collisionBox->rightCollision == false)
		{
			isMoving = true;
			ApplyForce(Vec3(mass * 2.0f, 0.0f, 0.0f));
		}
		else
		{
			isMoving = false;
		}
	}

	//W
	else if (moveForward == true)
	{
		if (collisionBox->frontCollision == false)
		{
			isMoving = true;
			ApplyForce(Vec3(0.0f, 0.0f, -mass * 2.0f));
		}
		else
		{
			isMoving = false;
		}
	}

	//A
	else if (moveLeft == true)
	{
		if (collisionBox->leftCollision == false)
		{
			isMoving = true;
			ApplyForce(Vec3(-mass * 2.0f, 0.0f, 0.0f));
		}
		else
		{
			isMoving = false;
		}
	}

	//S
	else if (moveBack == true)
	{
		if (collisionBox->backCollision == false)
		{
			isMoving = true;
			ApplyForce(Vec3(0.0f, 0.0f, mass * 2.0f));
		}
		else
		{
			isMoving = false;
		}
	}

	//No input being pressed, stop the player
	else if (moveBack == false && moveRight == false && moveForward == false && moveLeft == false && isJumping == false)
	{
		isMoving = false;
	}

	collisionBox->pos = pos;

	if (!collisionBox->bottomCollision)
	{
		applyGravity = true;
	}
	else
	{
		applyGravity = false;
	}
	
	if (applyGravity)
	{
		ApplyForce(Vec3(0.0f, -529.74f, 0.0f));
	}
	else
	{
		accel.y = 0.0f;
		vel.y = 0.0f;
	}

	if (!isMoving)
	{
		StopMoving();
	}

	HandleEvents(sdlEvent);
}

void PlayerCharacter::Render()
{
	Matrix3 normalMatrix = MatrixMath::transpose(MatrixMath::inverse(modelMatrix));

	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix.matrix4);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix.matrix3);

	mesh->Render();
}

void PlayerCharacter::OnDestroy() {}

void PlayerCharacter::ApplyForce(Vec3 force)
{
	accel.x = force.x / mass;
	accel.y = force.y / mass;
	accel.z = force.z / mass;
}

void PlayerCharacter::ApplyTorque(float torque)
{
	angularAcc = torque / rotationalInertia;
}

void PlayerCharacter::HandleEvents(SDL_Event& event_)
{
	while (SDL_PollEvent( &sdlEvent ))
	{
		if (sdlEvent.type == SDL_KEYDOWN)
		{
			// INPUT
			//Add more input buttons here. Remember to add the same buttons to the SDL_KEYUP section below, as well as functionality for it.
			switch (sdlEvent.key.keysym.sym)
			{
			case SDLK_d:
				moveRight = true;
				break;
			case SDLK_s:
				moveBack = true;
				break;
			case SDLK_a:
				moveLeft = true;
				break;
			case SDLK_w:
				moveForward = true;
				break;
			case SDLK_SPACE:
				if (canJump)
				{
					isJumping = true;
					isMoving = true;
					applyGravity = false;
					accel.y = 100.0f;
					//ApplyForce(Vec3(0.0f, 100.0f, 0.0f));
				}
				break;
			default:
				break;
			}
		}
		if (sdlEvent.type == SDL_KEYUP)
		{
			switch (sdlEvent.key.keysym.sym)
			{
			case SDLK_d:
				moveRight = false;
				break;
			case SDLK_s:
				moveBack = false;
				break;
			case SDLK_a:
				moveLeft = false;
				break;
			case SDLK_w:
				moveForward = false;
				break;
			default:
				break;
			}
		}
	}

	if (state[SDL_SCANCODE_Q])
	{
		angularVel = 300.0f;
	}
	else if (state[SDL_SCANCODE_E])
	{
		angularVel = -300.0f;
	}
	else
	{
		angularVel = 0.0f;
	}
}

void PlayerCharacter::StopMoving()
{
	vel.Zero();
	accel.Zero();
}
