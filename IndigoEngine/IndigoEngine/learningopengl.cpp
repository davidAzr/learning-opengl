#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "imageloader.h"
#include "camera.h"
#include "model.h"
#include "lights.h"

#define VERTEX_SHADER_FILEPATH "shaders/vs_cube.glsl" 
#define FRAGMENT_SHADER_FILEPATH "shaders/fs_twotextures.glsl" 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);


float SCR_WIDTH = 800.f;
float SCR_HEIGHT = 600.f;

float lastFrame;
float deltaTime;

float lastX, lastY;
bool firstMouse = true;

Camera camera;

int main() {
	// Inicializamos glfw
	glfwInit();
	// Configuramos glfw diciendole la version de OpenGL que
	// vamos a utilizar y el perfil, core-profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creamos el objeto de la ventana
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Inicializamos GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << '\n';
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	Shader lightCubeShaderProgram("shaders/vs_lightcube.glsl", "shaders/fs_lightcube.glsl");
	Shader lightedShaderProgram("shaders/vs_phonglighting.glsl", "shaders/fs_phonglighting.glsl");


	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Creamos el VBO, lo asignamos y le copiamos la informacion de los vertices
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAOlighted;
	glGenVertexArrays(1, &VAOlighted);

	glBindVertexArray(VAOlighted);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int VAOlightCube;
	glGenVertexArrays(1, &VAOlightCube);

	glBindVertexArray(VAOlightCube);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Textures
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("textures/sky.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data2 = stbi_load("textures/venus.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	stbi_image_free(data2);

	//shaderProgram.setInt("texture1", 0);
	//shaderProgram.setInt("texture2", 1);

	glm::mat4 projection;
	

	Model trackmodel("resources/models/slot_straight_track.obj");
	Model orangecar("resources/models/coche22.obj");
	Model whitecar("resources/models/coche1.obj");

	// Render loop
	while (!glfwWindowShouldClose(window)) {

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// input
		processInput(window);

		glClearColor(0.f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view;
		view = camera.GetViewMatrix();

		projection = glm::perspective(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

		glm::vec3 lightColor;
		lightColor.r = 1;
		lightColor.g = 1;
		lightColor.b = 0;

		glm::vec3 viewPos = camera.getPos();

		lightCubeShaderProgram.Use();

		float radius = 5.f;
		//glm::vec3 lightPos(sin(currentTime) * radius, 1.0f, cos(currentTime) * radius);
		glm::vec3 lightPos(0.f, 5.f, -5.f);
		glm::mat4 lightCubeModelMatrix(1.0f);
		lightCubeModelMatrix = glm::translate(lightCubeModelMatrix, lightPos);
		lightCubeModelMatrix = glm::scale(lightCubeModelMatrix, glm::vec3(0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightCubeModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightCubeShaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(glGetUniformLocation(lightCubeShaderProgram.ID, "lightColor"), 1, glm::value_ptr(lightColor));

		glBindVertexArray(VAOlightCube);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightedShaderProgram.Use();

		glm::mat4 lightedCubeModelMatrix(1.0f);
		lightedCubeModelMatrix = glm::translate(lightedCubeModelMatrix, glm::vec3(0.f, 0.f, 0.f));
		glUniformMatrix4fv(glGetUniformLocation(lightedShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightedCubeModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(lightedShaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightedShaderProgram.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		
		DirLight dirLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(-1.0f, -1.0f, 0.0f));
		//PointLight pointLight(glm::vec3(0.1f, 0.1f, 0.1f), lightColor, glm::vec3(1.0f, 1.0f, 0.0f), lightPos, 1.0f, 0.09f, 0.032f);
		glm::vec3 spotColor(1.0f, 1.0f, 0.0f);
		SpotLight spotLight(spotColor * 0.0f, spotColor, spotColor, lightPos, glm::vec3(0.f, -1.f, 0.f), glm::cos(glm::radians(20.f)), glm::cos(glm::radians(30.f)));
		lightedShaderProgram.setDirLight("dirlight", dirLight);
		//lightedShaderProgram.setPointLight("pointlight[0]", pointLight);
		lightedShaderProgram.setSpotLight("spotlight[0]", spotLight);
		glUniform1i(glGetUniformLocation(lightedShaderProgram.ID, "nPointLights"), 0);
		glUniform1i(glGetUniformLocation(lightedShaderProgram.ID, "nSpotLights"), 1);
		
		glUniform3fv(glGetUniformLocation(lightedShaderProgram.ID, "viewPos"), 1, glm::value_ptr(viewPos));

		trackmodel.Draw(lightedShaderProgram);
		
		glm::mat4 orangecarmodelmat(1.0f);
		orangecarmodelmat = glm::translate(orangecarmodelmat, glm::vec3(2.25f, 1.0f, 0.f + sin((float)glfwGetTime())));
		orangecarmodelmat = glm::scale(orangecarmodelmat, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(glGetUniformLocation(lightedShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(orangecarmodelmat));
		orangecar.Draw(lightedShaderProgram);
		
		glm::mat4 whitecarmodelmat(1.0f);
		whitecarmodelmat = glm::translate(whitecarmodelmat, glm::vec3(-2.25f, 1.3f, 0.f + cos((float)glfwGetTime())));
		whitecarmodelmat = glm::rotate(whitecarmodelmat, glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
		whitecarmodelmat = glm::scale(whitecarmodelmat, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(glGetUniformLocation(lightedShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(whitecarmodelmat));
		whitecar.Draw(lightedShaderProgram);


		
		//glBindVertexArray(VAOlighted);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// Callback function to be called each time the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	SCR_HEIGHT = height;
	SCR_WIDTH = width;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	direction movementDirection = NONE;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		movementDirection = FORWARD;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		movementDirection = BACKWARDS;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		movementDirection = LEFT;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		movementDirection = RIGHT;
	}
	camera.ProcessKeyboardInput(movementDirection, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	auto yoffset = lastY - ypos;
	auto xoffset = xpos - lastX;
	lastY = ypos;
	lastX = xpos;

	camera.ProcessMouseInput(xoffset, yoffset);
}