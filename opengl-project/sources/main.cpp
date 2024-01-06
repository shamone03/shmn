#include <main.h>
#include <optional>

#include <window/window.h>
#include <shader_tools/shader_tools.h>

const char* vertexShaderSource =
	"#version 460 core\n"
	"layout (location = 0) in vec3 pos;\n"
	"void main() {\n"
	"	gl_Position = vec4(pos.x, pos.y, pos.z, 1);\n"
	"}\0";

const char* fragShaderSource =
	"#version 460 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
	"}\0";

int main() {
	const auto window = window::initialize_window(1200, 1200);
	const auto programID = shader_tools::create_program(vertexShaderSource, fragShaderSource);
	if (!programID.has_value() || !window.has_value()) return 1;

	constexpr GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
   };
	const unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	
	GLuint vboID;
	glGenBuffers(1, &vboID);
	GLuint eboID;
	glGenBuffers(1, &eboID);
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds
	glBindVertexArray(0); // unbinds
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(*window)) {
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(*programID);
		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}