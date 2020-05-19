#pragma once

#include <iostream>

#include <string>

#include <glad/glad.h>

class Shader {

public:
	unsigned int ID;
	Shader(const std::string&, const std::string&);
	void Use();

};