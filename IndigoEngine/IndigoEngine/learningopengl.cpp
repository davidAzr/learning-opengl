#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// VERTEX SHADER
//#version 330 core
//layout(location = 0) in vec3 aPos;
//
//void main()
//{
//	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//}

// FRAGMENT SHADER
//#version 330 core
//out vec4 FragColor;
//
//void main() {
//	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
//}

float vertices[] = {
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	// Inicializamos glfw
	glfwInit();
	// Configuramos glfw diciendole la version de OpenGL que
	// vamos a utilizar y el perfil, core-profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creamos el objeto de la ventana
	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", NULL, NULL);
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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);

	// Creamos el VBO, lo asignamos y le copiamos la informacion de los vertices
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		glClearColor(0.6f, 0.1f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// Callback function to be called each time the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}