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
	glfwInit();
	glewInit();
	
	SceneManager* sceneMan = new SceneManager();

	if (sceneMan->Initialize("Window", 1280, 720) == true)
	{
		sceneMan->Run();
	}

	return 0;
}