#include "Scene1.h"
#include "MatrixMath.h"

Scene1::Scene1() : player(nullptr), camera(nullptr), sphere(nullptr), playerMesh(nullptr), shader(nullptr), isRunning(NULL), window(NULL)
{
	printTime = false;
	timer = new Timer;

	std::cout << "Scene 0 created." << std::endl;

	
}

Scene1::~Scene1()
{
}

bool Scene1::OnCreate()
{
	camera = new Camera();
	//light source used for the shader
	lightSource = Vec3(0.0f, -10.0f, -5.0f);
	if (camera == nullptr)
	{
		std::cout << "Camera not created properly." << std::endl;
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "Camera created." << std::endl;
	}

	/**
	TO-DO
	THIS (LOADING IN MESHES) SHOULD BE A FUNCTION.
	FOR EXAMPLE, I SHOULD BE ABLE TO DO mesh.applyOBJ AND THAT WILL USE ObjLoader::loadOBJ AND ASSIGN IT TO WHATEVER MESH CALLED applyOBJ.
	**/
	//Load in the file from the path specified. If it does not exist, break. If it does, let the debugger know it has been loaded succesfully.
	if (ObjLoader::loadOBJ("C:/GameDevelopment/Projects/Bullet/Dependencies/Meshes/Mario.obj") == false)
	{
		std::cout << "3D OBJ path provided not found.\n";
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "3D OBJ Loaded Succesfully.\n";
	}

	/* Set the playerMesh values, create the shader, create the sphere. */
	playerMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	if (ObjLoader::loadOBJ("C:/GameDevelopment/Projects/Bullet/Dependencies/Meshes/Sphere.obj") == false)
	{
		std::cout << "3D OBJ path provided not found.\n";
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "3D OBJ Loaded Succesfully.\n";
	}

	sphereMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	if (ObjLoader::loadOBJ("C:/GameDevelopment/Projects/Bullet/Dependencies/Meshes/Cube.obj") == false)
	{
		std::cout << "3D OBJ path provided not found.\n";
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "3D OBJ Loaded Succesfully.\n";
	}

	floorMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	shader = new Shader("C:/GameDevelopment/Projects/Bullet/Bullet/src/testShader.glsl");

	//Error check the scene shader.
	if (shader == nullptr)
	{
		std::cout << "The shader was not loaded in.\n";
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "Scene shader loaded\n";
	}

	player = new PlayerCharacter(playerMesh, shader, player->THIRD_PERSON);
	sphere = new Sphere(sphereMesh, shader);
	floor = new Cube(floorMesh, shader);
	//error check player creation.
	if (player == nullptr || sphere == nullptr)
	{
		std::cout << "A GameObject could not be created." << std::endl;
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "GameObjects has been created." << std::endl;
	}

	/* Get position of GameObjects, then set the model matrices for each to display the proper models in the proper locations. */
	floor->setPos(Vec3(0.0f, -2.0f, 0.0f));
	floor->collisionBox->size = Vec3(13.5f, 1.0f, 13.5f);
	floor->collisionBox->setPos(floor->pos);
	// TO-DO
	// MAKE A SCALE FUNCTION THAT SCALES THE MESH *AND* THE COLLISION BOX.
	floor->setModelMatrix(MatrixMath::translate(floor->getPos()).multiplyMat(MatrixMath::scale(Vec3(10.0f, 1.0f, 10.0f))));

	sphere->setPos(Vec3(5.0f, 1.0f, 0.0f));
	sphere->collisionBox->size = Vec3(1.0f, 1.0f, 1.0f);
	sphere->collisionBox->setPos(sphere->pos);
	sphere->setModelMatrix(MatrixMath::translate(sphere->getPos()));

	player->mass = 54.0f;
	player->setPos(Vec3(0.0f, 1.0f, 0.0f));
	player->collisionBox->setPos(player->pos);
	player->setModelMatrix(MatrixMath::translate(player->getPos()));


	// TO-DO
	// THIS WILL BE CODE TO SET THE CAMERA IN PLACE FOR THIRD PERSON, FIRST PERSON, OR TOP DOWN.
	/*if (player->THIRD_PERSON)
	{
		std::cout << "True" << std::endl;
		camera->translate = MatrixMath::translate(Vec3(player->pos.x, player->pos.y, player->pos.z));
	}*/

	return true;
}

void Scene1::HandleEvents(SDL_Event& sdlEvent)
{
	camera->HandleEvents(sdlEvent);
	switch (sdlEvent.type)
	{
	case SDL_QUIT: //Close window when close button is pressed
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_p: //Pause timer when P is pressed, then unpause if the timer is already paused and P is pressed again
			if (timer->isPaused() == false)
			{
				timer->Pause();
			}
			else if (timer->isPaused() == true)
			{
				timer->Unpause();
			}
			break;
		}
	}
}

void Scene1::Update(const float deltaTime)
{
	//Gets the current tick count on the timer and prints to console if printTime is set to true. (Can be changed via the constructor.)
	Uint32 currentTicks = timer->GetTicks();
	if (printTime == true)
	{
		std::cout << currentTicks << "\n";
	}

	player->collisionBox->CheckCollision(*floor->collisionBox);

	player->Update(deltaTime);
	player->setModelMatrix(MatrixMath::translate(player->getPos()).multiplyMat(MatrixMath::rotate(player->angle, Vec3(0.0f, 1.0f, 0.0f))));

	if (player->collisionBox->pos.y - (player->collisionBox->size.y / 2.0f) <= floor->collisionBox->pos.y + (floor->collisionBox->size.y / 2.0f) + 0.5f)
	{	
		player->canJump = true;
	}
	else
	{
		player->canJump = false;
	}

	if (player->collisionBox->bottomCollision == true)
	{
		player->isJumping = false;
	}

	camera->pos.x = -player->getPos().x;
	camera->pos.y = -player->getPos().y - 1.5f;
	camera->pos.z = -player->getPos().z;
	camera->Update(deltaTime);
	//Handle events and Render are called in SceneManager->GetEvents.
}

void Scene1::Render() const
{
	/* Set the BG colour and clear the screen for rendering. Enable depth. */
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/* Get and use the shader. */
	GLuint program = player->getShader()->getProgram();
	glUseProgram(program);

	/* Set the uniforms. */
	glUniformMatrix4fv(player->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix().matrix4);
	glUniformMatrix4fv(player->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix().matrix4);
	glUniform3fv(player->getShader()->getUniformID("lightPos"), 1, lightSource);

	glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix().matrix4);
	glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix().matrix4);
	glUniform3fv(sphere->getShader()->getUniformID("lightPos"), 1, lightSource);

	glUniformMatrix4fv(floor->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix().matrix4);
	glUniformMatrix4fv(floor->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix().matrix4);
	glUniform3fv(floor->getShader()->getUniformID("lightPos"), 1, lightSource);

	sphere->Render();
	player->Render();
	floor->Render();

	glUseProgram(0);
}

void Scene1::OnDestroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	glfwTerminate();
	delete(player, playerMesh, shader, this);
	std::cout << "Scene1 cleaned." << std::endl;
}