#include "vertex_array/vertex_array.h"

shmn::vertex_array::vertex_array::vertex_array() {
    glGenVertexArrays(1, &m_id);
}

void shmn::vertex_array::vertex_array::bind() const {
    glBindVertexArray(m_id);
}

void shmn::vertex_array::vertex_array::unbind() const {
    
}
