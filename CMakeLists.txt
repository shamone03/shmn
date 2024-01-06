cmake_minimum_required(VERSION 3.23)

project(opengl-project)
find_package(glfw3 REQUIRED CONFIG)
find_package(glad REQUIRED CONFIG)

set(SOURCES ${PROJECT_NAME}/sources/main.cpp)
set(INCLUDE ${PROJECT_NAME}/include/main.h)

add_executable(${PROJECT_NAME} ${INCLUDE} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
