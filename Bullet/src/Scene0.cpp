#include "Scene0.h"

SDL_Texture* playerTexture;
SDL_Rect srcRec, destRec;
SDL_Surface surface;

Scene0::Scene0()
{
	timer = new Timer;
	isRunning = NULL;
	window = NULL;
	renderer = new Renderer;
	sphere = new GameObject;
}

Scene0::~Scene0()
{

}

bool Scene0::OnCreate(const char* title, int xPos, int yPos, int width, int height, bool fullScreen)
{
	int flags = 0;
	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//***** BEGIN WINDOW CREATION AND INITIALIZATION *****//
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //If SDL and glfw initialize properly, create window and start timer.
	{
		std::cout << "Initialized properly." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
		if (window)
		{
			std::cout << "Window created" << std::endl;
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
	}
	//***** END WINDOW CREATION AND INITIALIZATION *****//

	//Load in the file from the path specified. If it does not exist, break. If it does, let the debugger know it has been loaded succesfully.
	if (ObjLoader::loadOBJ("C:/GameDevelopment/Projects/Bullet/Dependencies/Meshes/Sphere.obj") == false)
	{
		std::cout << "3D OBJ path provided not found.\n";
		return false;
	}
	else
	{
		std::cout << "3D OBJ Loaded Succesfully.\n";
	}

	//Set the loaded OBJ as a mesh.
	mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	
	return true;
}

void Scene0::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: //Close window when close button is pressed
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
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

void Scene0::Update()
{
	while (isRunning)
	{
		Uint32 currentTicks = timer->GetTicks();

		//std::cout << currentTicks << "\n";

		HandleEvents();
	}
}

void Scene0::Render() const
{

}

void Scene0::OnDestroy()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	glfwTerminate();
	delete(mesh);
	delete(this);
	std::cout << "Scene0 cleaned." << std::endl;
}