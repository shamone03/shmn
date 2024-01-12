#include "window/window.h"

#include <iostream>

shmn::window::window::window(const int width, const int height, const std::string_view title) :
m_width(width), m_height(height), m_title(title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_GLFWwindow = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (m_GLFWwindow == nullptr) {
        std::cerr << "No window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("No window");
    }
    
    glfwMakeContextCurrent(m_GLFWwindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "No GLAD" << std::endl;
        throw std::runtime_error("No GLAD");
    }
    glViewport(0, 0, width, height);

    shmn::utils::error::gl_check_error();
}

void shmn::window::window::update() const {
    swap_buffers();
    poll_events();
}

shmn::window::window::~window() {
    glfwTerminate();
}

void shmn::window::window::swap_buffers() const {
    glfwSwapBuffers(m_GLFWwindow);
}

void shmn::window::window::poll_events() {
    glfwPollEvents();
}

