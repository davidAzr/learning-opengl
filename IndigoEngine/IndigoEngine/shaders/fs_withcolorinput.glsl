#version 330 core

in vec3 colorInput;
out vec4 FragColor;

void main() {
	FragColor = vec4(colorInput, 1.0f);
}