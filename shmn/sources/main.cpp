#include "main.h"

#include <optional>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "buffer/buffer.h"
#include "examples/examples.h"
#include "shader/shader.h"
#include "utils/error.h"
#include "utils/stats.h"
#include "utils/utils.h"
#include "window/window.h"
// TODO: make class	
void process_input(shmn::window::window& window, bool& fill) {
	if (glfwGetKey(*window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		window.close();
	}
	if (glfwGetKey(*window, GLFW_KEY_P) == GLFW_PRESS) {
		fill = !fill;
		!fill ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void shmn::examples::draw_3d(shmn::window::window& window) {
	const auto shader = shmn::shader::shader("3d_vert.glsl", "3d_frag.glsl");
	std::vector<std::pair<GLuint, std::string>> textures = shmn::utils::get_textures({ "saul.jpg" });

	std::vector vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint vaoID;
	
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	const shmn::buffer::buffer vbo(GL_ARRAY_BUFFER, vertices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glEnable(GL_DEPTH_TEST);
	
	float delta = 0;
	float time = 0;

	shmn::transform::transform model;

	model.scale({.5f, .5f, .5f});
	std::srand(69);

	model.translate({std::rand() % 4, std::rand() % 2, std::rand() % 6});
	
	
	glm::mat4 view(1.f);
	view = glm::translate(view, {0, 0, -3.f});

	glm::mat4 projection(1.f);
	projection = glm::perspective(glm::radians(90.f), window.get_aspect(), .1f, 100.f);

	shader.use();
	for (int i = 0; i < textures.size(); i++) {
		shader.set_int(textures[i].second, i);
	}
	bool fillMode;
	while (window.is_open()) {
		process_input(window, fillMode);
		const auto start = glfwGetTime();
		glClearColor(.5f, .5f, .5f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		int i = 0;
		for (const auto& [id, name] : textures) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, id);
			i++;
		}
		
		shader.use();
		
		shader.set_mat("projection", projection);
		shader.set_mat("view", view);
		
		glBindVertexArray(vaoID);
		
		model.rotate(90 * delta, { 0, 1, 0});
		model.translate({0, std::sin(time) * .5f * delta, 0});


		shader.set_mat("model", model.get_transform());
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		window.update();
		shmn::utils::error::gl_check_error();
		
		delta = glfwGetTime() - start;
		time += delta;
		std::cout << shmn::utils::stats::get_stats(delta, time) << '\r';
	}

}

int main() {
	auto window = shmn::window::window(1600, 900, "saul");
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	
	shmn::examples::draw_3d(window);
	
	return 0;
}