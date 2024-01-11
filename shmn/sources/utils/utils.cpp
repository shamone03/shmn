#include "utils/utils.h"

#include <iostream>
#include <stb_image.h>
#include <string>
#include <vector>


std::vector<std::pair<GLuint, std::string>> shmn::utils::get_textures(const std::vector<std::string>& files) {
    std::vector<std::pair<GLuint, std::string>> textures;
    for (const auto& file : files) {
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
	
        auto name = file.substr(0, file.find('.'));
        auto ext = file.substr(name.length() + 1, file.find('.'));
	
        textures.emplace_back(id, name + "_" + ext);
	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, numChannels;
        stbi_set_flip_vertically_on_load(true);
        GLubyte* data = stbi_load(file.c_str(), &width, &height, &numChannels, 0);
	
        if (!data) {
            const auto message = "Unable to read " + file;
            std::cerr << message << std::endl;
            throw std::runtime_error(message);
        }
	
        if (numChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // first rgb is for output texture, second is for input image
        }
        if (numChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // first rgb is for output texture, second is for input image
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
	return textures;
}

