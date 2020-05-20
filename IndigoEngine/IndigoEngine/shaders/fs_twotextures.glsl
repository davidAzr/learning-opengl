#version 330 core

in vec3 colorInput;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main() {
	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), texture(texture2, texCoord).a * 1);
}