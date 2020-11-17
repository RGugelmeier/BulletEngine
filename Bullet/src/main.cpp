#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#undef main

#include "Scene0.h"
#include "Mesh.h"

int main(void)
{
	glfwInit();
	glewInit();
	Scene0* scene0 = new Scene0;

	scene0->OnCreate("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, false);
	scene0->Update();
	scene0->OnDestroy();

	return 0;
}