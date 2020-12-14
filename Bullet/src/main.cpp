#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#undef main

#include "SceneManager.h"
#include "Mesh.h"
#include "Shader.h"

int main(void)
{
	//Initialize glfw and glew
	glfwInit();
	glewInit();
	
	//Create the a scene manager object
	SceneManager* sceneMan = new SceneManager();

	//Initialize the scene
	if (sceneMan->Initialize("Window", 1280, 720) == true)
	{
		//Run the main game loop
		sceneMan->Run();
	}

	return 0;
}