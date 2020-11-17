#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

union SDL_Event;

class Scene {
public:
	Scene() {}
	~Scene() {}

	virtual bool OnCreate(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) = 0;
	virtual void OnDestroy() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents() = 0;
};
#endif