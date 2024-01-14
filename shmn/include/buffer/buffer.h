#pragma once
#include <vector>
#include <glad/glad.h>

namespace shmn::buffer {
    class buffer {
    public:
        buffer() = delete;
        buffer(GLenum type, const std::vector<GLfloat>& vertices);

        void bind() const;
        void set_vertices(const std::vector<GLfloat>& vertices);
        void unbind() const;
        
    private:
        GLenum m_type;
        GLuint m_id;
        std::vector<GLfloat> m_vertices;
    };
}
