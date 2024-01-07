#include "shader/shader.h"

#include <fstream>
#include <iostream>
#include <string>

#include "shader/shader_tools/shader_tools.h"

Shader::Shader(const std::string_view pathToVert, std::string_view path_to_frag) {
    const auto vertSource = get_source(pathToVert.data());
    const auto fragSource = get_source(path_to_frag.data());

    m_id = shader_tools::create_program(vertSource, fragSource);

    if (!m_id.has_value()) {
        const auto message = "Could not create shader program";
        std::cerr << message << std::endl;
        throw std::runtime_error(message);
    }
}

void Shader::use() const {
    glUseProgram(*m_id);
}

void Shader::set_float(const std::string_view name, const GLfloat value) const {
    const auto location = glGetUniformLocation(*m_id, name.data());
    check_uniform_location(location, name);
    glUniform1f(location, value);
}

void Shader::check_uniform_location(const GLint location, const std::string_view name) {
    if (location < 0) {
        const auto message = "No Uniform with name" + std::string(name.data());
        std::cerr << message << std::endl;
        throw std::invalid_argument(message);
    }
}

const char* Shader::get_source(const std::string_view path) {
    std::ifstream vertex(path.data());

    std::string source;
    if (vertex.is_open()) {
        std::string line;
        while (std::getline(vertex, line)) {
            source += line + '\n';
            line.clear();
        }
    } else {
        throw std::ios_base::failure("Could not open" + std::string(path.data()));
    }

    return source.c_str();
}

