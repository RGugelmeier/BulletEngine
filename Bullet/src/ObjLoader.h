#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <vector>
#include "Vec3.h"
#include "Vec2.h"

class ObjLoader {
public:

	/// C11 precautions 
	ObjLoader(const ObjLoader&) = delete;  /// Copy constructor
	ObjLoader(ObjLoader&&) = delete;       /// Move constructor
	ObjLoader& operator=(const ObjLoader&) = delete; /// Copy operator
	ObjLoader& operator=(ObjLoader&&) = delete;      /// Move operator

	/*
	vertices = mesh's vertices
	uvCoords = mesh's uv coordinates
	normals = mesh's normals
	loadOBJ(const char* path) = method to load the object. Takes in a path to find the OBJ file to load.
	*/
	static std::vector<Vec3> vertices;
	static std::vector<Vec2> uvCoords;
	static std::vector<Vec3> normals;
	static bool loadOBJ(const char* path);
};

#endif