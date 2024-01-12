#include "main.h"

#include <optional>
#include <fstream>
#include <string>
#include <vector>

#include "examples/examples.h"
#include "shader/shader.h"
#include "utils/error.h"
#include "utils/stats.h"
#include "utils/utils.h"
#include "window/window.h"
// TODO: make class	
void process_input(GLFWwindow* window, bool& fill) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		fill = !fill;
		!fill ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
void shmn::examples::draw_3d(GLFWwindow* window) {
const auto shader = shmn::shader::shader("3d_vert.glsl", "3d_frag.glsl");
	std::vector<std::pair<GLuint, std::string>> textures = shmn::utils::get_textures({ "saul.jpg" });

	constexpr float vertices[] {
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

	GLuint vboID, vaoID;
	{
		glGenBuffers(1, &vboID);
		glGenVertexArrays(1, &vaoID);

		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glEnable(GL_DEPTH_TEST);
	
	float delta = 0;
	float time = 0;

	shmn::transform::transform model;
	// model.rotate(-45.f, {1, 0, 0});
	model.scale({.5f, .5f, .5f});

	glm::mat4 view(1.f);
	view = glm::translate(view, {0, 0, -3.f});

	glm::mat4 projection(1.f);
	projection = glm::perspective(glm::radians(45.f), 1920.f / 1080.f, .1f, 100.f);

	shader.use();
	for (int i = 0; i < textures.size(); i++) {
		shader.set_int(textures[i].second, i);
	}
	while (!glfwWindowShouldClose(window)) {
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
		glfwSwapBuffers(window);
		glfwPollEvents();
		shmn::utils::error::gl_check_error();
		
		delta = glfwGetTime() - start;
		time += delta;
		std::cout << shmn::utils::stats::get_stats(delta, time) << '\r';
	}
	shmn::window::close_window();

}

int main() {
	const auto window = shmn::window::initialize_window(1600, 900, "saul");
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	
	shmn::examples::draw_3d(*window);
	shmn::window::close_window();
	
	return 0;
}