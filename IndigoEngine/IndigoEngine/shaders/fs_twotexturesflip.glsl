#version 330 core

in vec3 colorInput;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main() {
	vec2 newCoord = vec2(-1 * texCoord.x, texCoord.y);
	FragColor = mix(texture(texture1, texCoord), texture(texture2, newCoord), 0.5);
}