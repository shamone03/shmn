#include "transform/transform.h"

void shmn::transform::transform::rotate(const float angle, const glm::vec3& axis) {
    m_transformation = glm::rotate(m_transformation, glm::radians(angle), axis);
    m_rot += angle * axis;
}

void shmn::transform::transform::translate(const glm::vec3& trans) {
    m_transformation = glm::translate(m_transformation, trans);
    m_pos += trans;
}

void shmn::transform::transform::scale(const glm::vec3& scale) {
    m_transformation = glm::scale(m_transformation, scale);
    m_scl += scale;
}

glm::vec3 shmn::transform::transform::get_up() const {
    
}

glm::vec3 shmn::transform::transform::get_right() const {
}

glm::vec3 shmn::transform::transform::get_forward() const {
    return glm::cross(get_right(), get_up());
}

float const* shmn::transform::transform::get_data() const {
    return glm::value_ptr(m_transformation);
}

void shmn::transform::transform::clear() {
    m_transformation = glm::mat4(1.f);
    m_pos = {0, 0, 0};
    m_rot = {0, 0, 0};
    m_scl = {1, 1, 1};
}
