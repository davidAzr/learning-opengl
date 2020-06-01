#pragma once

#include <iostream>

#include <string>

#include <glad/glad.h>

#include "lights.h"

class Shader {

public:
	unsigned int ID;
	Shader(const std::string&, const std::string&);
	void Use();
	void setBool(const std::string& uniformName, bool value);
	void setInt(const std::string& uniformName, int value);
	void setFloat(const std::string& uniformName, float value);
	void setDirLight(const std::string& uniformName, DirLight dirlight);
	void setSpotLight(const std::string& uniformName, SpotLight spotlight);
	void setPointLight(const std::string& uniformName, PointLight pointlight);

private:
	void setLight(const std::string& uniformName, Light light);
};