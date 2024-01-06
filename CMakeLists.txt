cmake_minimum_required(VERSION 3.23)

project(conan-opengl-template)
find_package(glfw3 REQUIRED CONFIG)
find_package(glad REQUIRED CONFIG)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
