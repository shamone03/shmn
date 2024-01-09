#include "shader/shader.h"

#include <fstream>
#include <iostream>
#include <string>

#include "shader/shader_tools/shader_tools.h"

shmn::shader::Shader::Shader(const std::string_view pathToVert, const std::string_view pathToFrag) {
    const auto vertSource = get_source(pathToVert.data());
    const auto fragSource = get_source(pathToFrag.data());

    m_id = shader_tools::create_program(vertSource, fragSource);

    if (!m_id.has_value()) {
        const auto message = "Could not create shader program";
        std::cerr << message << std::endl;
        throw std::runtime_error(message);
    }
}

void shmn::shader::Shader::use() const {
    glUseProgram(*m_id);
}

void shmn::shader::Shader::set_float(const std::string_view name, const GLfloat value) const {
    const auto location = glGetUniformLocation(*m_id, name.data());
    check_uniform_location(location, name);
    glUniform1f(location, value);
}

void shmn::shader::Shader::set_int(std::string_view name, GLint value) const {
    const auto location = glGetUniformLocation(*m_id, name.data());
    check_uniform_location(location, name);
    glUniform1i(location, value);
}

void shmn::shader::Shader::check_uniform_location(const GLint location, const std::string_view name) {
    if (location < 0) {
        const auto message = "No Uniform with name: " + std::string(name.data());
        std::cerr << message << std::endl;
        throw std::invalid_argument(message);
    }
}

const char* shmn::shader::Shader::get_source(const std::string_view path) {
    std::ifstream vertex(path.data());

    std::string source;
    if (vertex.is_open()) {
        std::string line;
        while (std::getline(vertex, line)) {
            source += line + '\n';
            line.clear();
        }
    } else {
        const auto message = "Could not open" + std::string(path.data());
        std::cerr << message << std::endl;
        throw std::ios_base::failure(message);
    }

    return source.c_str();
}