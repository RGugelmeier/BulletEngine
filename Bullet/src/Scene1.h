#ifndef SCENE1_H
#define SCENE1_H

#include <iostream>

//Library includes
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// TO-DO
// ADD AN ARRAY SYSTEM FOR COLLISION BOXES AND MAYBE GAMEOBJECTS?

//Personally created class includes
#include "Scene.h"
#include "Sphere.h"
#include "SceneManager.h"
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
#include "Camera.h"
#include "Window.h"
#include "PlayerCharacter.h"
#include "Cube.h"
class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	/*
	OnCreate = Run once when the Scene is created. Take in values for window creation.
	HandeEvents = Run every itteration of the main loop. Checks for user input and other events.
	Update = Run every itteration of the main loop. Handles all updating to the window or program.
	Render = Run every itteration of the main loop. Used to render objects to the screen.
	Ondestroy = Called once at the end of the program. Used to clean up the program and do anything that must be done whenclosing the program.
	running() = Decides if the Scene is active and running.
	*/

	bool OnCreate() override;
	void HandleEvents(SDL_Event& sdlEvent) override;
	void Update(const float deltaTime) override;
	void Render() const override;
	void OnDestroy() override;
	inline bool running() { return isRunning; };

	inline PlayerCharacter GetPlayer() { return *player; };

private:

	/*
	isRunning = Holds if the Scene is running.
	sphere = a sphere.
	timer = The timer. Used to keep track of and handle time in the scene.
	window = The window.

	mesh = a test mesh for the scene.
	shader = The shader that will be used on this scene.
	renderer = the renderer. Used to render the scene.
	*/
	bool printTime;
	bool isRunning;
	Sphere* sphere;
	PlayerCharacter* player;
	Cube* floor;
	class Timer* timer;
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event* event;
	Mesh* playerMesh; //Mario
	Mesh* sphereMesh; //Sphere
	Mesh* floorMesh; //Cube
	Shader* shader;
	Renderer* renderer;
	Camera* camera;
	Vec3 lightSource;
	VertexArray* va;
	IndexBuffer* ib;
};

#endif // !Scene1