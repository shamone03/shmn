#pragma once
#include <string>
#include <vector>

#include <glad/glad.h>

namespace shmn::utils {
    std::vector<std::pair<GLuint, std::string>> get_textures(const std::vector<std::string>& files);
}