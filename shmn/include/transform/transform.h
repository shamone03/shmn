#pragma once
#include <glm/glm.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO: replace with strong type checking
#include "position.h"
#include "rotation.h"
#include "scale.h"

namespace shmn::transform {
    class transform final {
    public:
        ~transform() = default;
        transform() = default;
        
        transform(const transform&) = default;
        transform& operator=(const transform&) = delete;
        transform(transform&&) = delete;
        transform& operator=(const transform&&) = delete;

        transform(const position position, const rotation rotation, const scale scale)
            : m_pos(position), m_rot(rotation), m_scl(scale) {}
        
        glm::vec3 get_position() const { return m_pos; }
        glm::vec3 get_rotation() const { return m_rot; }
        glm::vec3 get_scale() const { return m_scl; }
        glm::mat4 get_transform() const { return m_transformation; }

        void set_forward(const glm::vec3& forward);
        glm::vec3 get_up() const;
        glm::vec3 get_right() const;
        glm::vec3 get_forward() const;

        void rotate(float angle, const glm::vec3& axis);
        void translate(const glm::vec3& trans);
        void scale(const glm::vec3& scale);
        float const* get_data() const;
        void clear();
        // transform operator*(const transform& other) const {
        //     // TODO: find a way to get the pos, rot and scl to return a shmn::transform::transform with the correct member vars
        //     // return m_transformation * other.get_transform();
        //     return {};
        // }

    private:
        glm::mat4 m_transformation = glm::mat4(1.f);
        glm::vec3 m_forward{0, 0, 1};
        // user convenience
        glm::vec3 m_pos{0.f, 0.f, 0.f};
        glm::vec3 m_rot{0.f, 0.f , 0.f};
        glm::vec3 m_scl{1.f, 1.f, 1.f};
        
    };

}
