#pragma once
#include <glad/glad.h>

namespace shmn::vertex_array {
    class vertex_array {
    public:
        vertex_array();
        void bind() const;
        void unbind() const;
        GLuint get_id() const { return m_id; }
    private:
        GLuint m_id;
    };
} 
