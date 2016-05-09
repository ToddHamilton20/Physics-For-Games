#pragma once

#include "Mesh.h"

class Camera;

class GameObject
{
public:
	virtual void Update(float a_deltaTime) {}
	virtual void Draw(Camera* a_camera, glm::vec3 a_colour);

protected:
	Mesh mesh;
};

class PhysicsGameObject
{
public:
protected:
};