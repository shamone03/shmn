#pragma once
#include <optional>
#include <xstring>
#include <glad/glad.h>

namespace shmn::shader::shader_tools {
    std::optional<GLuint> create_program(std::string_view vertSource, std::string_view fragSource);
}
