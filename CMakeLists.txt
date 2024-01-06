cmake_minimum_required(VERSION 3.23)

project(opengl-project)

find_package(glfw3 REQUIRED CONFIG)
find_package(glad REQUIRED CONFIG)

set(SOURCES 
    ${PROJECT_NAME}/sources/main.cpp
    ${PROJECT_NAME}/sources/window/window.cpp
    ${PROJECT_NAME}/sources/shader_tools/shader_tools.cpp
)
set(INCLUDE 
    ${PROJECT_NAME}/include/main.h
    ${PROJECT_NAME}/include/window/window.h
    ${PROJECT_NAME}/include/shader_tools/shader_tools.h
)

add_executable(${PROJECT_NAME} ${INCLUDE} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
