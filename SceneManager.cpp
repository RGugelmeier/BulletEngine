#include <SDL.h>
#include "SceneManager.h"

#include "Scene0.h"

SceneManager::SceneManager() :
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false) {}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	//Debug::Info("Deleting the GameSceneManager", __FILE__, __LINE__);

}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		std::cout << "Failed to initialize Window object" << std::endl;
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		std::cout << "Failed to initialize Timer object" << std::endl;
		return false;
	}

	BuildScene(SCENE0);

	return true;
}


void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		GetEvents();
		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::GetEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;

			case SDL_SCANCODE_F1:
				BuildScene(SCENE1);
				break;

			case SDL_SCANCODE_F2:
				BuildScene(SCENE2);
				break;

			case SDL_SCANCODE_F3:
				BuildScene(SCENE3);
				break;

			case SDL_SCANCODE_F4:
				BuildScene(SCENE4);
				break;

			case SDL_SCANCODE_F5:
				BuildScene(SCENE5);
				break;

			case SDL_SCANCODE_F6:
				BuildScene(SCENE6);
				break;

			default:
				BuildScene(SCENE0);
				break;
			}
		}
		if (currentScene == nullptr) {
			std::cout << "Could not initialize scene." << std::endl;
			isRunning = false;
			return;
		}

		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildScene(SCENE_NUMBER scene) {
	bool status;

	if (currentScene != nullptr) {
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE0:
		currentScene = new Scene0();
		status = currentScene->OnCreate();
		break;

	case SCENE1:
		//currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;

	case SCENE2:
		//currentScene = new Scene2();
		status = currentScene->OnCreate();
		break;

	case SCENE3:
		//currentScene = new Scene3();
		status = currentScene->OnCreate();
		break;

	case SCENE4:
		//currentScene = new Scene4();
		status = currentScene->OnCreate();
		break;

	case SCENE5:
		//currentScene = new Scene5();
		status = currentScene->OnCreate();
		break;

	case SCENE6:
		//currentScene = new Scene6();
		status = currentScene->OnCreate();
		break;

	default:
		std::cout << "Invalid scene number set in scene manager." << std::endl;
		currentScene = nullptr;
		break;
	}
}


