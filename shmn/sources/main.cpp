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

void shmn::examples::draw_3d(GLFWwindow* window) {
	const auto shader = shmn::shader::shader("3d_vert.glsl", "3d_frag.glsl");
	std::vector<std::pair<GLuint, std::string>> textures = shmn::utils::get_textures({"hamster.png", "saul.jpg" });

	constexpr float vertices[] {
		// positions          // colors           // texture coords
		.5f,  .5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		.5f, -.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	   -.5f, -.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	   -.5f,  .5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
   };

	constexpr GLuint indices[] {
		0, 1, 2,
		2, 3, 0
	};
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

	float delta;
	float sum = 0;

	shmn::transform::transform model;
	model.rotate(-20.f, {1, 0, 0});

	glm::mat4 view(1.f);
	view = glm::translate(view, {0, 0, -3.f});

	glm::mat4 projection(1.f);
	projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);

	int i = 0;
	shader.use();
	for (const auto& [id, name] : textures) {
		shader.set_int(name, i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, id);
		i++;
	}
	
	while (!glfwWindowShouldClose(window)) {
		const auto start = glfwGetTime();
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// shader.use();
		shader.set_mat("projection", projection);
		shader.set_mat("view", view);

		model.rotate(90 * delta, { 0, 1, 0});
		shader.set_mat("model", model.get_transform());
		
		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glfwSwapBuffers(window);
		glfwPollEvents();
		shmn::utils::error::gl_check_error();
		
		delta = glfwGetTime() - start;
		sum += delta;
		std::cout << shmn::utils::stats::get_stats(delta, sum) << '\r';
	}
	shmn::window::close_window();
}

int main() {
	const auto window = shmn::window::initialize_window(1080, 1080, "saul");
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	
	shmn::examples::draw_3d(*window);
	shmn::window::close_window();
	
	return 0;
}