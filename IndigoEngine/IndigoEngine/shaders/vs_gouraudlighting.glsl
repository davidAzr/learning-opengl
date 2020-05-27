#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 vertexColor;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1);

	vec3 worldPos = vec3(model *  vec4(aPos, 1));

	// Ambient
	float ambientIntensity = 0.1;
	vec3 ambientLight = lightColor * ambientIntensity;
	
	// Diffuse
	vec3 lightDir = normalize(lightPos -  worldPos);
	vec3 normal = normalize(aNorm);
	float diffuseIntensity = max(dot(lightDir, normal), 0.0f);
	vec3 diffuseLight = lightColor * diffuseIntensity;

	// Specular;
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	vec3 viewDir = normalize(viewPos - worldPos);
	float specularStrength = 1, shininess =32;
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), shininess);
	vec3 specularLight = spec * specularStrength * lightColor;

	vertexColor = vec4((ambientLight + diffuseLight + specularLight) * objectColor, 1.0f);
}