#pragma once

#include "glm\glm.hpp"

class Camera;

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh() : initialised(false) {}
	~Mesh();
	void LoadOBJ(const char* a_objFilePath, bool a_yFlip = false);
	void Draw(Camera* a_camera, glm::vec3 a_colour);

private:
	bool initialised;
	unsigned int shapeCount;
	unsigned int *indexCounts;

	unsigned int *vao, *vbo, *ibo;
};