#pragma once
#include "game_object/game_object.h"
#include "transform/transform.h"

namespace shmn::camera {
    class camera final : public shmn::game_object::game_object {
    public:
        ~camera() override;
        void update(GLfloat delta) override;
        void start() override;
        shmn::transform::transform& get_transform() override { return m_transform; }

    private:
        shmn::transform::transform m_transform;
    };
}
