#include <main.h>
#include <optional>

namespace window {
	std::optional<GLFWwindow*> initialize_window(const int width, const int height) {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, "Hi", NULL, NULL);
		if (window == nullptr) {
			std::cout << "No window" << std::endl;
			glfwTerminate();
			return std::nullopt;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
			std::cout << "No GLAD" << std::endl;
			return std::nullopt;
		}
		glViewport(0, 0, width, height);

		return window;
	}
}

namespace shader_tools {
	namespace {
		std::optional<GLuint> compile_shader(const GLuint type, const char* source) {
			const GLuint id = glCreateShader(type);
			glShaderSource(id, 1, &source, NULL);
			glCompileShader(id);
			
			// error check
			GLint success = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				char log[512];
				glGetShaderInfoLog(id, 512, NULL, log);
				const std::string name = type == GL_VERTEX_SHADER ? "VERTEX " : "FRAGMENT ";
				std::cout << name << "SHADER DID NOT COMPILE ERROR: " << log << std::endl;
				return std::nullopt;
			}
			
			return id;
		}
	}
	
	std::optional<GLuint> create_program(const char* vertSource, const char* fragSource) {
		const auto vertexShaderID = compile_shader(GL_VERTEX_SHADER, vertSource);
		const auto fragShaderID = compile_shader(GL_FRAGMENT_SHADER, fragSource);

		if (!vertexShaderID.has_value() || !fragShaderID.has_value()) return std::nullopt;
		
		const GLuint programID = glCreateProgram();
		glAttachShader(programID, *vertexShaderID);
		glAttachShader(programID, *fragShaderID);
		glLinkProgram(programID);
	
		// error check
		GLint success = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success) {
			char log[512];
			glGetProgramInfoLog(programID, 512, NULL, log);
			std::cout << "SHADER PROGRAM DID NOT LINK ERROR: " << log << std::endl;
			return std::nullopt;
		}
	
		glDeleteShader(*vertexShaderID);
		glDeleteShader(*fragShaderID);
		return programID;
	}

}

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
	const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	
	GLuint vboID;
	glGenBuffers(1, &vboID);
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds
	glBindVertexArray(0); // unbinds
	
	while(!glfwWindowShouldClose(*window)) {
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(*programID);
		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}