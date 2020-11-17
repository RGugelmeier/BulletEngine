#pragma once

#include <Vector>
#include <GL/glew.h>
#include <GL/GL.h>
#include "Vec3.h"
#include "Vec2.h"

/*
public:
verticies = the mesh's verticies
normals = the mesh's normals
coords = the positrions for UV mapping
indicies = the index values for the mesh

Render() = the function called to render the mesh

private:
vao = The vertex array object
vbo = the vertex buffer object

setupMesh() = the function called to set the mesh's values
*/

class Mesh
{
public:
	GLenum drawmode;
	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Vec2> uvCoords;
	std::vector<GLuint> indices;

	Mesh(GLenum drawmode_, std::vector<Vec3>&, std::vector<Vec3>&, std::vector<Vec2>&);
	~Mesh();
	void Render() const;

private:
	GLuint vao;
	GLuint vbo;
	void setupMesh();
};

