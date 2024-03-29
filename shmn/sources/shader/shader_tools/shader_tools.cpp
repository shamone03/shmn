#include "shader/shader_tools/shader_tools.h"

#include <iostream>
#include <optional>

namespace {
    std::optional<GLuint> compile_shader(const GLuint type, const char* source) {
        const GLuint id = glCreateShader(type);
        glShaderSource(id, 1, &source, NULL);
        glCompileShader(id);
        
        // error check
        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(id, 512, NULL, log);
            const std::string name = type == GL_VERTEX_SHADER ? "VERTEX " : "FRAGMENT ";
            std::cout << name << "SHADER DID NOT COMPILE ERROR: " << log << std::endl;
            return std::nullopt;
        }
        
        return id;
    }
}

std::optional<GLuint> shmn::shader::shader_tools::create_program(std::string_view vertSource, std::string_view fragSource) {
    const auto vertexShaderID = compile_shader(GL_VERTEX_SHADER, vertSource.data());
    const auto fragShaderID = compile_shader(GL_FRAGMENT_SHADER, fragSource.data());

    if (!vertexShaderID.has_value() || !fragShaderID.has_value()) return std::nullopt;

    const GLuint programID = glCreateProgram();
    glAttachShader(programID, *vertexShaderID);
    glAttachShader(programID, *fragShaderID);
    glLinkProgram(programID);
	
    // error check
    GLint success = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(programID, 512, NULL, log);
        std::cout << "SHADER PROGRAM DID NOT LINK ERROR: " << log << std::endl;
        return std::nullopt;
    }
	
    glDeleteShader(*vertexShaderID);
    glDeleteShader(*fragShaderID);
    return programID;
}
