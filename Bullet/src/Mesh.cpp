#include "Mesh.h"

Mesh::Mesh(GLenum drawmode_, std::vector<Vec3> &verticies_, std::vector<Vec3> &normals_, std::vector<Vec2> &uvCoords_)
{
	//Initialize all mesh aspects, then run setup mesh.
	drawmode = drawmode_;
	this->vertices = verticies_;
	this->normals = normals_;
	this->uvCoords = uvCoords_;
	this->setupMesh();
}

Mesh::~Mesh()
{
	//Delete vertex array and buffer to clean up.
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::setupMesh()
{
//Define the lengths of each vertex, normal, and coord to make them easier to use and understand.
#define VERTEX_LENGTH (vertices.size() * (sizeof(Vec3)))
#define NORMAL_LENGTH (normals.size() * (sizeof(Vec3)))
#define TEXCOORD_LENGTH (uvCoords.size() * (sizeof(Vec2)))
	const int verticiesID = 0;
	const int normalsID = 1;
	const int uvCoordsID = 2;

	//Create and bind the vertex array object (An object that contains one or more vertex buffer)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Create and initialize the vertex buffer object (An object that contains methods for giving render information to the GPU)
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH, NULL, GL_STATIC_DRAW);

	//Assign the address of verticies to be the beginning of the array buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, &vertices[0]);
	//Assign the address of normals to the next spot after the verticies in the array buffer using the length of the vertecies as the offset.
	glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, &normals[0]);
	//Assign the address of texture coordinates to the next spot after the normals in the array buffer using the length of the vertecies and the normals as the offset.
	glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH, TEXCOORD_LENGTH, &uvCoords[0]);

	//Enable the verticies, normals, and coords by ID, then create a pointer for them.
	glEnableVertexAttribArray(verticiesID);
	glVertexAttribPointer(verticiesID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

	glEnableVertexAttribArray(normalsID);
	glVertexAttribPointer(normalsID, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH));

	glEnableVertexAttribArray(uvCoordsID);
	glVertexAttribPointer(uvCoordsID, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(VERTEX_LENGTH + NORMAL_LENGTH));

//Undefine previous definitions
#undef VERTEX_LENGTH
#undef NORMAL_LENGTH
#undef TEXCOORD_LENGTH
}

void Mesh::Render() const
{
	//Bind vertex array object, then draw, then unbind the vertex array object.
	glBindVertexArray(vao);
	glDrawArrays(drawmode, 0, vertices.size());
	glBindVertexArray(0); // Unbind the VAO
}