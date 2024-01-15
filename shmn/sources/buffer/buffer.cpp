#include "buffer/buffer.h"

#include "utils/error.h"

shmn::buffer::buffer::buffer(GLenum type): m_type(type) {
    glGenBuffers(1, &m_id);
}

shmn::buffer::buffer::~buffer() {
    unbind();
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
