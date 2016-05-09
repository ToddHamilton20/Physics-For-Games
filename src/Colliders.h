#pragma once

#include "Transform.h"
#include <glm\glm.hpp>

class Collider
{
public:
	virtual ~Collider() = 0;
	inline Transform GetTransform() { return transform; }
	inline Transform SetTransform(Transform a_transform) { transform = a_transform; }

private:
	Transform transform;
};

namespace Colliders
{
	struct AABB : public Collider
	{
		glm::vec3 centre;
		glm::vec3 extents;
	};

	struct OOBB : public Collider
	{
		glm::vec3 centre;
		glm::vec3 extents;
		glm::vec3 rotation;
	};

	struct Sphere : public Collider
	{
		glm::vec3 centre;
		float radius;
	};

	struct Plane : public Collider
	{
		glm::vec3 normal;
		float distance;
	};

	struct Capsule : public Collider
	{
		glm::vec3 position;
		float length;
		float radius;
		float ritation;
	};
};