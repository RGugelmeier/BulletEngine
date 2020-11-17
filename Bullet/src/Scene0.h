#ifndef SCENE0_H
#define SCENE0_H

#include <iostream>

//Library includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Personally created class includes
#include "Scene.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Timer.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mesh.h"
#include "ObjLoader.h"

class Scene0 : Scene
{
public:
	Scene0();
	~Scene0();

	/*
	OnCreate = Run once when the Scene is created
	HandeEvents = Run every itteration of the main loop. Checks for user input and other events.
	Update = Run every itteration of the main loop. Handles all updating to the window or program.
	Render = Run every itteration of the main loop. Used to render objects to the screen.
	Ondestroy = Called once at the end of the program. Used to clean up the program and do anything that must be done whenclosing the program.
	running() = Decides if the Scene is active and running.	
	*/
	bool OnCreate(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) override;
	void HandleEvents() override;
	void Update() override;
	void Render() const override;
	void OnDestroy() override;
	inline bool running() { return isRunning; };

private:

	/*
	isRunning = Holds if the Scene is running.
	sphere = a sphere.
	renderer = the renderer. Used to render the scene.
	timer = The timer. Used to keep track of and handle time in the scene.
	window = The window.

	mesh = a test mesh for the scene.
	*/
	bool isRunning;
	GameObject* sphere;
	Renderer* renderer;
	class Timer* timer;
	SDL_Window* window;
	SDL_GLContext context;
	Mesh* mesh;
};

#endif // !Scene0