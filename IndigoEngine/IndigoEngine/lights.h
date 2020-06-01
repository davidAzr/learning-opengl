#pragma once
#include <glm/glm.hpp>

struct Light {
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : ambient(ambient), diffuse(diffuse), specular(specular) {}
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct DirLight : Light {
	DirLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction) : Light(ambient, diffuse, specular), direction(direction) {}
	
	glm::vec3 direction;
};

struct PointLight : Light {
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic) 
		: Light(ambient, diffuse, specular), position(position), constant(constant), linear(linear), quadratic(quadratic){}
	
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight : Light {
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, float constant, float innercutoff, float outercutoff)
		: Light(ambient, diffuse, specular), position(position), direction(direction), innercutoff(innercutoff), outercutoff(outercutoff) {}
	
	glm::vec3  position;
	glm::vec3  direction;
	float innercutoff;
	float outercutoff;
};
