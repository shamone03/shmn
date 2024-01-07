#pragma once
#include <optional>
#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader(std::string_view pathToVert, std::string_view path_to_frag);

    void use() const;

    void set_float(std::string_view name, GLfloat value) const;
private:
    static void check_uniform_location(GLint location, std::string_view name);
    
    static const char* get_source(std::string_view path);
    std::optional<GLuint> m_id;
};
