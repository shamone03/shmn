#include <main.h>
#include <optional>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <glm/ext/matrix_transform.hpp>

#include "shader/shader.h"
#include "utils/error.h"
#include "utils/stats.h"
#include "window/window.h"

namespace shmn::examples {
	void draw_shapes() {
		const auto window = shmn::window::initialize_window(1200, 1200, "shape");
		const shmn::shader::shader shader("vert.glsl", "frag.glsl");
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
		const shmn::shader::shader shader("texture_vert.glsl", "texture_frag.glsl");
		
		constexpr auto version = 0.3;

		
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
			0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		   -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		   -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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

	void draw_transformations(GLFWwindow* window) {
		
		const auto shader = shmn::shader::shader("transform_vert.glsl", "transform_frag.glsl");
		
		const std::vector<std::string> files = {"saul.jpg", "hamster.png" };
		std::vector<GLuint> textures{};

		constexpr float vertices[] = {
			// positions          // colors           // texture coords
			0.9f,  0.9f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			0.9f, -0.9f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		   -0.9f, -0.9f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		   -0.9f,  0.9f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	   };

		const GLuint indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		
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
		
		GLuint vboID, eboID, vaoID;
		{   
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
		}
		
		shmn::transform::transform transform[2];
		float delta = 0.0;
		float curRotation = 0;
		float sum = 0;
		
		while (!glfwWindowShouldClose(window)) {
			const auto start = glfwGetTime();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (auto i = 0; i < textures.size(); i++) {
				shader.use();
				transform[i].rotate(delta * 90 / 20, glm::vec3(0, 0, 1));

				shader.set_mat("transform", transform[i].get_transform());
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
			
			glfwSwapBuffers(window);
			glfwPollEvents();
			
			delta = glfwGetTime() - start;
			sum += delta;
			std::cout << shmn::utils::stats::get_stats(delta, sum) << '\r';
			shmn::utils::error::gl_check_error();
		} 

	}
}

int main() {
	const auto window = shmn::window::initialize_window(1080, 1080, "saul");
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	shmn::examples::draw_transformations(*window);
	shmn::window::close_window();
	
	return 0;
}