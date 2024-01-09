#include <main.h>
#include <optional>
#include <fstream>
#include <string>
#include <vector>

#include "shader/shader.h"
#include "window/window.h"

namespace shmn::examples {
	void draw_shapes() {
		const auto window = shmn::window::initialize_window(1200, 1200, "shape");
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

	void draw_image() {
		const auto window = shmn::window::initialize_window(360, 360, "saul");
		const shmn::shader::Shader shader("texture_vert.glsl", "texture_frag.glsl");
		
		constexpr auto version = 0.3;
		// std::cout << "Shader Version: " << version << std::endl;
		
		const std::vector<std::string> files = {"saul.jpg", "hamster.png" };
		std::vector<GLuint> textures{};

		for (const auto& file : files) {
			GLuint id;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			textures.push_back(id);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
			int width, height, numChannels;
			stbi_set_flip_vertically_on_load(true);
			GLubyte* data = stbi_load(file.c_str(), &width, &height, &numChannels, 0);
			
			if (!data) {
				const auto message = "Unable to read " + file;
				std::cerr << message << std::endl;
				throw std::runtime_error(message);
			}
			if (numChannels == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // first rgb is for output texture, second is for input image
			}
			if (numChannels == 3) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // first rgb is for output texture, second is for input image
			}
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		
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

		for (auto i = 0; i < textures.size(); i++) {
			shader.use();
			if (files[i] == "saul.jpg") {
				shader.set_int("saul_jpg", i);
			}
			if (files[i] == "hamster.png") {
				shader.set_int("hamster_png", i);
			}
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
		
		while (!glfwWindowShouldClose(*window)) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (auto i = 0; i < textures.size(); i++) {
				shader.use();
				if (files[i] == "saul.jpg") {
					shader.set_int("saul_jpg", i);
				}
				if (files[i] == "hamster.png") {
					shader.set_int("hamster_png", i);
				}
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textures[i]);
				
				glBindVertexArray(vaoID);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			}


			glfwSwapBuffers(*window);
			glfwPollEvents();
		}
		
		shmn::window::close_window();
	}
}

int main() {
	shmn::examples::draw_image();
	return 0;
}