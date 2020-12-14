#include "Scene0.h"
#include "MatrixMath.h"

Scene0::Scene0() : camera(nullptr), mesh(nullptr), shader(nullptr), isRunning(NULL), window(NULL)
{
	printTime = false;
	timer = new Timer;

	std::cout << "Scene 0 created." << std::endl;
}

Scene0::~Scene0()
{

}

bool Scene0::OnCreate()
{
	camera = new Camera();
	lightSource = Vec3(-5.0f, 10.0f, -5.0f);
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

	/* Set the mesh values, create the shader, create the sphere. */
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
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

	/* Set the model matrix to display the proper model. */

	return true;
}

void Scene0::HandleEvents(SDL_Event& sdlEvent)
{
	SDL_PollEvent(&sdlEvent);
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

void Scene0::Update(const float deltaTime)
{
	//Gets the current tick count on the timer and prints to console if printTime is set to true. (Can be changed via the constructor.)
	Uint32 currentTicks = timer->GetTicks();
	if (printTime == true)
	{
		std::cout << currentTicks << "\n";
	}
	//sphere->ApplyForce(Vec3(0.0f, -1.0f, 0.0f));
	//sphere->Update(deltaTime);
	//sphere->setModelMatrix(MatrixMath::translate(sphere->getPos()));
	//Handle events and Render are called in SceneManager->GetEvents.
}

void Scene0::Render() const
{
	/* Set the BG colour and clear the screen for rendering. Enable depth. */
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/* Get and use the shader. */
	//GLuint program = sphere->getShader()->getProgram();
	//glUseProgram(program);

	/* Set the uniforms. */
	//glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix().matrix4);
	//glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix().matrix4);
	//glUniform3fv(sphere->getShader()->getUniformID("lightPos"), 1, lightSource);

	//sphere->Render();

	glUseProgram(0);
}

void Scene0::OnDestroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	glfwTerminate();
	delete(mesh, shader, this);
	std::cout << "Scene0 cleaned." << std::endl;
}