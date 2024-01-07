#include <main.h>
#include <optional>
#include <fstream>
#include <string>

#include <window/window.h>
#include <shader_tools/shader_tools.h>

// const char* vertexShaderSource =
// 	"#version 460 core\n"
// 	"layout (location = 0) in vec3 pos;\n"
// 	"out vec4 color;\n"
// 	"void main() {\n"
// 	"	gl_Position = vec4(pos.x, pos.y, pos.z, 1);\n"
// 	"	color = vec4(pos, 1);\n"
// 	"}\0";
//
// const char* fragShaderSource =
// 	"#version 460 core\n"
// 	"out vec4 FragColor;\n"
// 	"in vec4 color;\n"
// 	"void main() {\n"
// 	"	FragColor = color;\n"
// 	"}\0";

const std::string vertexShaderSource = R"(
	#version 460 core
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec3 color;
	
	out vec4 vertColor;

	void main() {
	    gl_Position = vec4(pos, 1);
		vertColor = vec4(color, 1);
	}
)";

const std::string fragShaderSource = R"(
	#version 460 core
	out vec4 outColor;
	in vec4 vertColor;

	uniform vec4 setColor;

	void main() {
	    outColor = vertColor;
		
	}
)";

int main() {
	const auto window = window::initialize_window(1200, 1200);
	const auto programID = shader_tools::create_program(vertexShaderSource.c_str(), fragShaderSource.c_str());
	if (!programID.has_value() || !window.has_value()) return 1;

	// const auto colorUniformLocation = glGetUniformLocation(*programID, "setColor");

	// if (colorUniformLocation < 0) {
	// 	std::cout << "Could not find uniform" << std::endl;
	// 	return 1;
	// }
	
	constexpr GLfloat vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
   };
	constexpr GLuint indices[] = {  // note that we start from 0!
		0, 1, 2
	};
	
	GLuint vboID, eboID, vaoID;
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &eboID);
	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds
	glBindVertexArray(0); // unbinds
	
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while(!glfwWindowShouldClose(*window)) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(*programID);

		// glUniform4f(colorUniformLocation, red, std::abs(std::cos(glfwGetTime())), red, 1.0f);
		
		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);

		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}