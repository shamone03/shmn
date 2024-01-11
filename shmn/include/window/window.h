#pragma once
#include "utils/error.h"

#include <optional>
#include <GLFW/glfw3.h>

namespace shmn::window {
    std::optional<GLFWwindow*> initialize_window(int width, int height, std::string_view title);
    void close_window();
}
