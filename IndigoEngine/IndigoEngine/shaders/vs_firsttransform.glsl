#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 aTransformMatrix;

out vec3 colorInput;
out vec2 texCoord;

void main() {
	colorInput = aColor;
	texCoord = aTexCoord;
	gl_Position = aTransformMatrix * vec4(aPos, 1.0f);
}