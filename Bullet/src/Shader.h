#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

//Used as the return type for ParseShader. That way you can return two strings from one function, the vertex and fragment shader strings.
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	/*
	std::string m_FilePath = The path where the mesh information text file is located.
	unsigned int m_RendererID = ID to the renderer.
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader);
	int GetUniformLocation(const std::string& name);
	*/
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertShader, const std::string& fragShader);

public:
	Shader(const std::string& filePath);
	~Shader();

	GLuint getUniformID(std::string name);
	inline GLuint getProgram() const { return m_RendererID; }

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void setUniformLocations();
};