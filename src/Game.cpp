#include "__macros__only_hpp.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Window.hpp"
#include "ErrorHandler.hpp"
#include "GL_TYPES.hpp"

#include "ImageLoader.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

int main() {

	// Initialization
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);

	if (!window.init())
		return -1;

	float vertices[] = {
    	-0.5f, -0.5f, 0.0f,  // bottom left corner
    	0.5f, -0.5f, 0.0f,   // bottom right corner
    	0.5f, 0.5f, 0.0f,    // top right corner
    	-0.5f, 0.5f, 0.0f    // top left corner
	};

	unsigned int indices[] = {
    	0, 1, 2,   // first triangle
    	2, 3, 0    // second triangle
	};

	
	GL_TYPES::VO vo1;
	glGenVertexArrays(1, &vo1.VAO);
	glGenBuffers(1, &vo1.VBO);
	glGenBuffers(1, &vo1.EBO);

	// Bind vo1.VAO
	glBindVertexArray(vo1.VAO);

	// Bind vo1.VBO and copy vertices data into it
	glBindBuffer(GL_ARRAY_BUFFER, vo1.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind vo1.EBO and copy indices data into it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vo1.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind vo1.VBO and vo1.VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	Shader shader1("assets/shaders/shader.v.glsl", "assets/shaders/shader.f.glsl");

	while (!window.shouldClose()) {

		window.pollEvents();

		glBindVertexArray(vo1.VAO);
		glUseProgram(shader1.id);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		window.processInput();
		window.swapBuffers();
	}

	return 0;
}