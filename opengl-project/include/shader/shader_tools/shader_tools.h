#pragma once
#include <optional>
#include <glad/glad.h>

namespace shader_tools {
    std::optional<GLuint> create_program(const char* vertSource, const char* fragSource);
}
