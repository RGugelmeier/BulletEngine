#include <stdio.h>
#include <string>
#include <cstring>
#include "ObjLoader.h"

// Initializing vectors
std::vector<Vec3> ObjLoader::normals;
std::vector<Vec3> ObjLoader::vertices;
std::vector<Vec2> ObjLoader::uvCoords;

bool ObjLoader::loadOBJ(const char* path) {
	printf("Loading OBJ file %s...\n", path);
	//Clear values.
	normals.clear();
	vertices.clear();
	uvCoords.clear();

	//Create variables for temporary mesh values
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vec3> temp_vertices;
	std::vector<Vec2> temp_uvs;
	std::vector<Vec3> temp_normals;

	/* Find and open the OBJ file */
	FILE* file;
	fopen_s(&file, path, "r");
	if (file == nullptr) {
		printf("Can't open your file %s \n", path);
		return false;
	}


	while (true) {
		char lineHeader[128];
		/// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF) {
			break; /// EOF is End of File. Done loading.
		}
		//Compare if the lineheader (First word of line) is "v" (Vertex), then add the values on that line into a vertex point (x, y, z).
		if (strcmp(lineHeader, "v") == 0) {
			Vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//Compare if the lineheader (First word of line) is "vt" (uvCoord), then add the values on that line into a uvCoordinate point (x, y, z).
		else if (strcmp(lineHeader, "vt") == 0) {
			Vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; /// Grr 
			temp_uvs.push_back(uv);
		}
		//Compare if the lineheader (First word of line) is "vn" (Normal), then add the values on that line into a normalized point (x, y, z).
		else if (strcmp(lineHeader, "vn") == 0) {
			Vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//Compare if the lineheader (First word of line) is "f" (Face), then add the values on that line into a Face value using all of the verticies, normals, and UV coordinates.
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//If there are not 3 verticies it will not work. This makes it so there are only triangles. (3 verticies, each with an x y z = 9 values.)
			if (matches != 9) {
				printf("Error: Can't read the file - this is a dumb reader");
				return false;
			}
			//Push all of the face values into their respective arrays to store them.
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		//If there is anything else starting the line, do not use it.
		else {
			char overflowCharacters[1000];
			fgets(overflowCharacters, 1000, file);
		}

	}

	/// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vec3 vertex = temp_vertices[vertexIndex - 1];
		Vec2 uv = temp_uvs[uvIndex - 1];
		Vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvCoords.push_back(uv);
		normals.push_back(normal);
	}
	return true;
}