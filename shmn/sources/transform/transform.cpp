#include "transform/transform.h"

void shmn::transform::transform::rotate(const float angle, const glm::vec3& axis) {
    m_transformation = glm::rotate(m_transformation, glm::radians(angle), axis);
    m_forward *= m_transformation; // ?
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

void shmn::transform::transform::set_forward(const glm::vec3& forward) {
    m_forward = forward;
}

glm::vec3 shmn::transform::transform::get_up() const {
    return glm::normalize(glm::cross(m_forward, get_right()));
}

glm::vec3 shmn::transform::transform::get_right() const {
    // cross with world up
    return glm::normalize(glm::cross({0, 1, 0}, m_forward));
}

glm::vec3 shmn::transform::transform::get_forward() const {
    return m_forward;
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
