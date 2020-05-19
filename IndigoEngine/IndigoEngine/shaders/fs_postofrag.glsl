#version 330 core

in vec3 position;
out vec4 FragColor;

void main() {
	FragColor = vec4(position, 1.0f);
}

// bottom left turns black because the position values are -05 -05 0 so the color we get is 0 0 0 black 