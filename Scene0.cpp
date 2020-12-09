#include "Scene0.h"
#include "MatrixMath.h"

SDL_Texture* playerTexture;
SDL_Rect srcRec, destRec;
SDL_Surface surface;

Scene0::Scene0() : camera(nullptr), sphere(nullptr), mesh(nullptr), shader(nullptr), isRunning(NULL), window(NULL)
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
	int flags = 0;
	//Set fullscreen window or not.
	/*if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}*/

	//***** BEGIN WINDOW CREATION AND INITIALIZATION *****//
	/*if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //If SDL and glfw initialize properly, create window and start timer.
	{
		std::cout << "SDL Initialized properly." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
		if (window)
		{
			std::cout << "SDL window created" << std::endl;
		}
		context = SDL_GL_CreateContext(window);

		//Starts glew
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			std::cout << "GLFW Error: " << glGetError() << std::endl;
			return false;
		}

		isRunning = true;
		timer->Start();
	}
	else if(SDL_Init(SDL_INIT_EVERYTHING != 0)) //Else print error and end
	{
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		isRunning = false;
	}*/
	//***** END WINDOW CREATION AND INITIALIZATION *****//



	camera = new Camera();
	lightSource = Vec3(0.0f, 0.0f, -5.0f);
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

	//Set the loaded OBJ as a mesh.
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shader = new Shader("Bullet/src/testShader.glsl");
	sphere = new GameObject(mesh, shader);

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

	//error check sphere creation.
	if (sphere == nullptr)
	{
		std::cout << "The GameObject was not created." << std::endl;
		return false;
		isRunning = false;
	}
	else
	{
		std::cout << "GameObject has been created." << std::endl;
	}

	//Set position of sphere, then set the model matrix to display the proper matrix.
	sphere->setPos(Vec3(-5.0f, 0.0f, 0.0f));
	sphere->setModelMatrix(MatrixMath::translate(sphere->getPos()));

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
	while (isRunning)
	{
		//Gets the current tick count on the timer and prints to console if printTime is set to true. (Can be changed via the constructor.)
		Uint32 currentTicks = timer->GetTicks();
		if (printTime == true)
		{
		std::cout << currentTicks << "\n";
		}
		sphere->Update(deltaTime);
		//Handle events is called in SceneManager->GetEvents.
		Render();
	}
}

void Scene0::Render() const
{
	glClearColor(1.0f, 0.6f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint program = sphere->getShader()->getProgram();
	glUseProgram(program);

	glUniformMatrix4fv(sphere->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix().matrix4);
	glUniformMatrix4fv(sphere->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix().matrix4);
	glUniform3fv(sphere->getShader()->getUniformID("lightPos"), 1, lightSource);

	sphere->Render();

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