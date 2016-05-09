#pragma once

#include <vector>

class Collider;

class PhysicsRenderer
{
public:

	std::vector<Collider*> colliders;
	
	void RenderCollisions();

private:
	unsigned int shader;
};