#pragma once
#include <glad/glad.h>

#include "transform/transform.h"

namespace shmn::game_object {
    class game_object {
    public:
        game_object() = default;
        virtual ~game_object() = default;
        virtual void start() = 0;
        virtual void update(GLfloat delta) = 0;
        virtual shmn::transform::transform& get_transform() = 0;
    };
}
