#pragma once
#include <optional>
#include <GLFW/glfw3.h>

namespace window {
    std::optional<GLFWwindow*> initialize_window(const int width, const int height);
}
