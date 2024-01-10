#include "transform/transform.h"

void shmn::transform::transform::rotate(float angle, glm::vec3 axis) {
    m_transformation = glm::rotate(m_transformation, glm::radians(angle), axis);
    m_rot += angle * axis;
}
        
void shmn::transform::transform::translate(glm::vec3 trans) {
    m_transformation = glm::translate(m_transformation, trans);
    m_pos += trans;
}
        
void shmn::transform::transform::scale(glm::vec3 scale) {
    m_transformation = glm::scale(m_transformation, scale);
    m_scl += scale;
}

float const* shmn::transform::transform::get_data() const {
    return glm::value_ptr(m_transformation);
}