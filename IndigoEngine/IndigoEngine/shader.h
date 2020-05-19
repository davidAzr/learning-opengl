#pragma once

#include <iostream>

#include <string>

#include <glad/glad.h>

class Shader {

public:
	unsigned int ID;
	Shader(const std::string&, const std::string&);
	void Use();
	void setBool(const std::string& uniformName, bool value);
	void setInt(const std::string& uniformName, int value);
	void setFloat(const std::string& uniformName, float value);
};