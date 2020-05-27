#version 330 core 

in vec3 Normal;
in vec3 FragPos; 

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

void main() {
	// Ambient
	float ambientLightIntensity = 0.1;
	vec3 ambientLight = ambientLightIntensity * lightColor;

	vec3 lightDirection = normalize(lightPos - FragPos);
	vec3 normal = normalize(Normal);
	
	// Diffuse
	float diffuseLightIntensity = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseLight = diffuseLightIntensity * lightColor;
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDirection, normal);
	float shininess = 32, specularStrength = 0.5;
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), shininess);
	vec3 specular = spec * specularStrength * lightColor;

	FragColor = vec4((ambientLight + diffuseLight + specular) * objectColor, 1.0f);
}