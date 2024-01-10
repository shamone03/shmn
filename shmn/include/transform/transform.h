#pragma once
#include <glm/glm.hpp>

// TODO: replace with strong type checking
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "position.h"
#include "rotation.h"
#include "scale.h"

namespace shmn::transform {
    class transform final {
    public:
        ~transform() = default;

        transform() :
            m_pos(0, 0, 0),
            m_rot(0, 0, 0),
            m_scl(1, 1, 1) {}
        
        transform(const transform&) = delete;
        transform& operator=(const transform&) = delete;
        transform(transform&&) = delete;
        transform& operator=(const transform&&) = delete;

        transform(const position position, const rotation rotation, const scale scale)
            : m_pos(position), m_rot(rotation), m_scl(scale) {}

        void set_rotation(const rotation& rot) { m_rot = rot; }
        void set_position(const position& pos) { m_pos = pos; }
        void set_scale(const scale& scale) { m_scl = scale; }

        glm::vec3 get_position() const { return m_pos; }
        glm::vec3 get_rotation() const { return m_rot; }
        glm::vec3 get_scale() const { return m_scl; }

        glm::mat4 get_transform() const { return m_transformation; }
        
        void rotate(float angle, glm::vec3 axis) {
            m_transformation = glm::rotate(m_transformation, glm::radians(angle), axis);
            m_rot += angle * axis;
        }
        
        void translate(glm::vec3 trans) {
            m_transformation = glm::translate(m_transformation, trans);
            m_pos += trans;
        }
        
        void scale(glm::vec3 scale) {
            m_transformation = glm::scale(m_transformation, scale);
            m_scl += scale;
        }
        
        float const* get_data() const {
            return glm::value_ptr(m_transformation);
        }

    private:
        glm::mat4 m_transformation = glm::mat4(1.f);

        // user convenience
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scl;
    };

}
