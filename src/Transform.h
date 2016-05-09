#pragma once

#include <glm/ext.hpp>
#include <vector>
#include <algorithm>
#include <imgui.h>

class mat4;

class Transform
{
public:
	Transform();
	Transform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale, Transform* a_parent = nullptr);

	void InitImGUI();
	glm::mat4 GetGlobalTransform();
	glm::mat4 GetLocalTransform();

	void SetParent(Transform* a_parentNode);
	Transform* GetParent();

	void TranslateBy(glm::vec3 a_translation);
	void RotateBy(glm::vec3 a_rotation);
	void ScaleBy(glm::vec3 a_scale);

	void SetPosition(glm::vec3 a_position)	{ position = a_position; }
	void SetRotation(glm::vec3 a_rotation)	{ rotation = a_rotation; }
	void SetScale(glm::vec3 a_scale)		{ scale = a_scale; }

	inline glm::vec3 GetPosition()	{ return position; }
	inline glm::vec3 GetRotation()	{ return rotation; }
	inline glm::vec3 GetScale()		{ return scale; }

	glm::vec3 GetGlobalPositon();
	glm::vec3 GetGlobalRotation();
	glm::vec3 GetGlobalScale();
	
private:
	Transform* parent;
	std::vector<Transform*> children;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};