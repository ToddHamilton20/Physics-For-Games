#include "Mesh.h"

#include "gl_core_4_4.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh::~Mesh()
{
	if (initialised)
	{
		glDeleteBuffers(shapeCount, vbo);
		glDeleteBuffers(shapeCount, ibo);
		glDeleteVertexArrays(shapeCount, vao);

		delete[] vbo;
		delete[] ibo;
		delete[] vao;
		delete[] indexCounts;
	}
}

void Mesh::LoadOBJ(const char* a_objFilePath, bool a_yFlip)
{
	if (!initialised)
	{
		initialised = true;

		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string error = "";

		std::string file = a_objFilePath;
		std::string folder = file.substr(0, file.find_last_of('/') + 1);

		bool success = tinyobj::LoadObj(shapes, materials, error,
			a_objFilePath, folder.c_str());

		if (!success)
			printf("%s\n", error.c_str());

		shapeCount = shapes.size();
		if (shapeCount > 0)
		{
			vbo = new unsigned int[shapeCount];
			ibo = new unsigned int[shapeCount];
			vao = new unsigned int[shapeCount];

			indexCounts = new unsigned int[shapeCount];

			glGenBuffers(shapeCount, vbo);
			glGenBuffers(shapeCount, ibo);
			glGenVertexArrays(shapeCount, vao);

			for (unsigned int i = 0; i < shapeCount; i++)
			{
				glBindVertexArray(vao[i]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

				glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					shapes[i].mesh.indices.size() * sizeof(unsigned int),
					shapes[i].mesh.indices.data(), GL_STATIC_DRAW);

				bool hasPosition = shapes[i].mesh.positions.empty() == false;
				bool hasTexture = shapes[i].mesh.texcoords.empty() == false;

				std::vector<Vertex> vertices;
				vertices.resize(shapes[i].mesh.positions.size() / 3);
				unsigned int vertCount = vertices.size();

				for (unsigned int j = 0; j < vertCount; j++)
				{
					if (hasPosition)
						vertices[j].position = glm::vec3(shapes[i].mesh.positions[j * 3 + 0], shapes[i].mesh.positions[j * 3 + 1], shapes[i].mesh.positions[j * 3 + 2]);
					if (hasTexture)
						vertices[j].texCoord = glm::vec2(shapes[i].mesh.texcoords[j * 2 + 0], a_yFlip ? 1.0f - shapes[i].mesh.texcoords[j * 2 + 1] : shapes[i].mesh.texcoords[j * 2 + 1]);
				}

				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
}

void Mesh::Draw(Camera* a_camera, glm::vec3 a_colour)
{
	if (initialised)
	{
		for (int i = 0; i < shapeCount; i++)
		{
			glBindVertexArray(vao[i]);
			glDrawElements(GL_TRIANGLES, indexCounts[i], GL_UNSIGNED_INT, 0);
		}
	}
}