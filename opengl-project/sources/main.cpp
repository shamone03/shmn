#include <main.h>
#include <optional>

namespace window {
	constexpr auto WIDTH = 1200;
	constexpr auto HEIGHT = 1200;
	std::optional<GLFWwindow*> initialize_window() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hi", NULL, NULL);
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
		glViewport(0, 0, WIDTH, HEIGHT);

		return window;
	}
}

int main() {
	const auto window = window::initialize_window();
	
	if (!window.has_value()) return 1;
	
	while(!glfwWindowShouldClose(*window)) {
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}