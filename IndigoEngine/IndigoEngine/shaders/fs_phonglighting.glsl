#version 330 core 
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
	vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
	vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
	vec3  position;
    vec3  direction;
    float innercutoff;
	float outercutoff;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 Normal;
in vec3 FragPos; 

uniform Material material;
uniform Light light;  
uniform SpotLight spotlight;  
uniform DirLight dirlight;  
uniform PointLight pointlight;  
uniform vec3 viewPos;

out vec4 FragColor;

vec3 CalcDirLight(DirLight light) {
	// Ambient
	vec3 ambientLight = material.ambient * light.ambient * light.diffuse;

	vec3 lightDirection = normalize(-light.direction);
	vec3 normal = normalize(Normal);
	
	// Diffuse
	float diffuseLightIntensity = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseLight = (diffuseLightIntensity * material.diffuse) * light.diffuse;
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDirection, normal);
	float shininess = 32, specularStrength = 0.5;
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = (spec * material.specular) * light.specular;
	return ambientLight + diffuseLight + specular;
}

vec3 CalcPointLight(PointLight light) {
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance * light.quadratic * pow(distance, 2));
	
	// Ambient
	vec3 ambientLight = material.ambient * light.ambient * light.diffuse;

	vec3 lightDirection = normalize(light.position - FragPos);
	vec3 normal = normalize(Normal);
	
	// Diffuse
	float diffuseLightIntensity = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseLight = (diffuseLightIntensity * material.diffuse) * light.diffuse;
	
	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDirection, normal);
	float shininess = 32, specularStrength = 0.5;
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = (spec * material.specular) * light.specular;
	return (ambientLight + diffuseLight + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light) {
	vec3 lightDirection = normalize(light.position - FragPos);
	
	float theta = dot(lightDirection, normalize(-light.direction));
	if(theta > light.outercutoff) {
		float epsilon = light.innercutoff - light.outercutoff;
		float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0f,  1.0f);

		// Ambient
		vec3 ambientLight = material.ambient * light.ambient * light.diffuse;

		vec3 lightDirection = normalize(light.position - FragPos);
		vec3 normal = normalize(Normal);
	
		// Diffuse
		float diffuseLightIntensity = max(dot(lightDirection, normal), 0.0f);
		vec3 diffuseLight = (diffuseLightIntensity * material.diffuse) * light.diffuse;
	
		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDirection, normal);
		float shininess = 32, specularStrength = 0.5;
		float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
		vec3 specular = (spec * material.specular) * light.specular;

		return ambientLight + diffuseLight * intensity + specular * intensity;
	}

	else {
		return material.ambient * light.ambient * light.diffuse;
	}
	
}




void main() {
	
	FragColor = vec4(CalcPointLight(pointlight), 1.0f);
}