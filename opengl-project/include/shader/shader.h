#pragma once
#include <optional>
#include <string>
#include <glad/glad.h>
#include <glm/fwd.hpp>

namespace shmn::shader {
    class shader {
    public:
        shader(std::string_view pathToVert, std::string_view pathToFrag);

        void use() const;
        
        // void set_mat(std::string_view name, glm::mat4 value) const;
        void set_float(std::string_view name, GLfloat value) const;
        void set_int(std::string_view name, GLint value) const;
    private:
        static void check_uniform_location(GLint location, std::string_view name);
        
        static const char* get_source(std::string_view path);
        std::optional<GLuint> m_id;
    };

}
