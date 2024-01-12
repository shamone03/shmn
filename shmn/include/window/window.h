#pragma once
#include "utils/error.h"

#include <optional>
#include <GLFW/glfw3.h>

namespace shmn::window {
    class window {
    public:
        window(int width, int height, std::string_view title);
        ~window();

        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
        std::string get_title() const { return m_title; }

        GLfloat get_aspect() const { return static_cast<GLfloat>(m_width) / static_cast<GLfloat>(m_height); }

        GLFWwindow* operator*() const { return m_GLFWwindow; }

        void swap_buffers() const;
        void update() const;
        
        static void poll_events();
    private:
        int m_width;
        int m_height;
        std::string m_title;
        GLFWwindow* m_GLFWwindow;
    };
}
