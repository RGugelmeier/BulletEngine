#include "Window.h"
Window::Window() : window(nullptr) {}

Window::~Window() {
	OnDestroy();
}

//Creates a window with the name, width, and height given. Initializes sdl and sets a context to be used to code with OpenGL. Then sets the attributes for OpenGl and SDL by getting
//the current OpenGL info and running setAttributes()
bool Window::OnCreate(std::string name_, int width_, int height_) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		return false;
	}

	this->width = width_;
	this->height = height_;
	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cout << "Failed to create window." << std::endl;
		return false;
	}
	context = SDL_GL_CreateContext(window);
	int major, minor;
	getInstalledOpenGLInfo(&major, &minor);
	setAttributes(major, minor);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "GLEW initialization failed." << std::endl;
		return false;
	}
	glViewport(0, 0, width, height);
	return true;
}

void Window::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::getHeight() {
	return height;
}

int Window::getWidth() {
	return width;
}

SDL_Window* Window::getWindow() const {
	return window;
}

//Gets the OpenGL info. Used to initialize OpenGL
void Window::getInstalledOpenGLInfo(int* major, int* minor) {
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);


	glGetIntegerv(GL_MAJOR_VERSION, major);
	glGetIntegerv(GL_MINOR_VERSION, minor);

	return;
}

void Window::setAttributes(int major_, int minor_) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
	return;
}

