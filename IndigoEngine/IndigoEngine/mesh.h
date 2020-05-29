#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

enum TextureType {
	Diffuse = 0,
	Specular
};

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	TextureType type;
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class Mesh
{
	public:
		std::vector<Vertex>			vertices;
		std::vector<unsigned int>	indices;
		std::vector<Texture>		textures;
		Material					material;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);
		void Draw(Shader& shader) const;

	private:
		unsigned int VAO, VBO, EBO;
	
		void setupMesh();
};

