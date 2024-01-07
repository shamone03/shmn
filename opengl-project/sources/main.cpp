#include <main.h>
#include <optional>
#include <fstream>
#include <string>

#include "shader/shader.h"
#include "window/window.h"

namespace shmn::examples {
	void example1() {
		const auto window = shmn::window::initialize_window(1200, 1200);
		const shmn::shader::Shader shader("vert.glsl", "frag.glsl");
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

			shader.use();
			shader.set_float("setColor", std::abs(std::sin(glfwGetTime())));
		
			glBindVertexArray(vaoID);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
			glBindVertexArray(0);

			glfwSwapBuffers(*window);
			glfwPollEvents();
		}

		shmn::window::close_window();
	}

	void example2() {
		const auto window = shmn::window::initialize_window(720, 720);
		const shmn::shader::Shader shader("texture_vert.glsl", "texture_frag.glsl");
		
		GLuint textureID;
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, numChannels;
		const std::string fileName = "saul.jpg";
		GLubyte* data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);
		if (!data) {
			const auto message = "Unable to read " + fileName;
			std::cerr << message << std::endl;
			throw std::runtime_error(message);
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // first rgb is for output texture, second is for input image
		stbi_image_free(data);
		glGenerateMipmap(GL_TEXTURE_2D);

		constexpr float vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	   };

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		
		while (!glfwWindowShouldClose(*window)) {
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			shader.use();

			glBindTexture(GL_TEXTURE_2D, textureID);
			glBindVertexArray(vaoID);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			glBindVertexArray(0);

			glfwSwapBuffers(*window);
			glfwPollEvents();
		}
		
		shmn::window::close_window();
	}
}

int main() {

	shmn::examples::example2();
	

	return 0;
}