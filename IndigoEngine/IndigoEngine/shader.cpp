#include "shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::string shaderSource, fileLine;
	std::ifstream shaderFile;

	// Loading and compiling vertexShader
	// Loading source from file
	shaderFile.open(vertexShaderPath.c_str(), std::ios::in);
	if (shaderFile.is_open()) {
		std::stringstream shaderFileStream;
		shaderFileStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderSource = shaderFileStream.str();
	}
	// Creating and compiling
	const char* vShaderCode = shaderSource.c_str();
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// Checking compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILDE" << '\n' << infoLog << '\n';
	}

	// Loading and compiling fragmentShader
	// Loading source from file
	shaderFile.open(fragmentShaderPath.c_str(), std::ios::in);
	if (shaderFile.is_open()) {
		std::stringstream shaderFileStream;
		shaderFileStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderSource = shaderFileStream.str();
	}
	// Creating and compiling
	const char* fShaderCode = shaderSource.c_str();
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// Checking compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << '\n' << infoLog << '\n';
	}

	// Creating shader program and adding loaded shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	// Checking for linking errors
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << '\n' << infoLog << '\n';
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string & uniformName, bool value)
{
	glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
}

void Shader::setInt(const std::string & uniformName, int value)
{
	glUniform1i(glGetUniformLocation(ID, uniformName.c_str()), value);
}

void Shader::setFloat(const std::string & uniformName, float value)
{
	glUniform1f(glGetUniformLocation(ID, uniformName.c_str()), value);
}
