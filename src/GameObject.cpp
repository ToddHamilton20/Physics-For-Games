#include "GameObject.h"

#include "Camera.h"

void GameObject::Draw(Camera* a_camera, glm::vec3 a_colour)
{
	mesh.Draw(a_camera, a_colour);
}