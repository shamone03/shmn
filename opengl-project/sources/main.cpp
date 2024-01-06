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

int main() {
	const auto window = window::initialize_window(1200, 1200);
	
	if (!window.has_value()) return 1;
	
	while(!glfwWindowShouldClose(*window)) {
		glfwSwapBuffers(*window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}