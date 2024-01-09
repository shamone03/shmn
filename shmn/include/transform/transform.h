#pragma once
#include <glm/glm.hpp>

// TODO: replace with strong type checking
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

        position get_position() const { return m_pos; }
        rotation get_rotation() const { return m_rot; }
        scale get_scale() const { return m_scl; }

    private:
        position m_pos;
        rotation m_rot;
        scale m_scl;
    };

}
