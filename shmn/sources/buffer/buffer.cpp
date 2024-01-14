#include "buffer/buffer.h"

#include "utils/error.h"

shmn::buffer::buffer::buffer(GLenum type, const std::vector<GLfloat>& vertices): m_type(type), m_vertices(vertices) {
    glGenBuffers(1, &m_id);
    bind(); // bind then buffer data!
    set_vertices(vertices);
}

void shmn::buffer::buffer::bind() const {
    glBindBuffer(m_type, m_id);
}

void shmn::buffer::buffer::set_vertices(const std::vector<GLfloat>& vertices) {
    m_vertices = vertices;
    glBufferData(m_type, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
}

void shmn::buffer::buffer::unbind() const {
    glBindBuffer(m_type, 0);
}
