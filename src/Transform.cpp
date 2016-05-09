#include "Transform.h"

Transform::Transform() :
	position(glm::vec3(0, 0, 0)),
	rotation(glm::vec3(0, 0, 0)),
	scale(glm::vec3(1, 1, 1)),
	parent(nullptr),
	children(std::vector<Transform*>())
{}

Transform::Transform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale, Transform* a_parent) :
	position(a_position),
	rotation(a_rotation),
	scale(a_scale),
	parent(a_parent),
	children(std::vector<Transform*>())
{}

void Transform::InitImGUI()
{
	if(ImGui::CollapsingHeader("Translation"))
	{
		ImGui::DragFloat("tX", &position.x, 0.1f);
		ImGui::DragFloat("tY", &position.y, 0.1f);
		ImGui::DragFloat("tZ", &position.z, 0.1f);
	}
	if (ImGui::CollapsingHeader("Rotation"))
	{
		float speed = glm::pi<float>() / 20.0f;
		ImGui::DragFloat("rX", &rotation.x, speed);
		ImGui::DragFloat("rY", &rotation.y, speed);
		ImGui::DragFloat("rZ", &rotation.z, speed);
	}
	if (ImGui::CollapsingHeader("Scale"))
	{
		ImGui::DragFloat("sX", &scale.x, 0.1f);
		ImGui::DragFloat("sY", &scale.y, 0.1f);
		ImGui::DragFloat("sZ", &scale.z, 0.1f);
	}
}

glm::mat4 Transform::GetGlobalTransform()
{
	glm::mat4 parentMatrix = parent != nullptr ? parent->GetGlobalTransform() : glm::mat4(1);
	return parentMatrix * glm::translate(position) * glm::toMat4(glm::quat(rotation)) * glm::scale(scale);
}

glm::mat4 Transform::GetLocalTransform()
{
	return glm::translate(position) * glm::toMat4(glm::quat(rotation)) * glm::scale(scale);
}

void Transform::SetParent(Transform* a_parentNode)
{
	if (parent != nullptr)
	{
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
	}

	parent = a_parentNode;
	if (std::find(parent->children.begin(), parent->children.end(), this) == parent->children.end())
		parent->children.push_back(this);
}

Transform* Transform::GetParent()
{
	return parent;
}

void Transform::TranslateBy(glm::vec3 a_translation)
{
	position += a_translation;
}

glm::vec3 Transform::GetGlobalPositon()
{
	return parent != nullptr ? parent->GetGlobalPositon() + position : position;
}

void Transform::RotateBy(glm::vec3 a_rotation)
{
	rotation = rotation * glm::quat(a_rotation);
}

glm::vec3 Transform::GetGlobalRotation()
{
	return parent != nullptr ? parent->GetGlobalRotation() * glm::quat(rotation) : rotation;
}

void Transform::ScaleBy(glm::vec3 a_scale)
{
	scale *= a_scale;
}

glm::vec3 Transform::GetGlobalScale()
{
	return parent != nullptr ? parent->GetGlobalScale() * scale : scale;
}