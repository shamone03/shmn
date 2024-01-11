#include "main.h"

#include <optional>
#include <fstream>
#include <string>

#include "examples/examples.h"
#include "shader/shader.h"
#include "utils/error.h"
#include "window/window.h"


int main() {
	const auto window = shmn::window::initialize_window(1080, 1080, "saul");
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	shmn::examples::draw_transformations(*window);
	shmn::window::close_window();
	
	return 0;
}