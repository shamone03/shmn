cmake_minimum_required(VERSION 3.23)
project(shmn)

find_package(glfw3 REQUIRED CONFIG)
find_package(glad REQUIRED CONFIG)
find_package(stb REQUIRED CONFIG)
find_package(glm REQUIRED CONFIG)

set(SOURCES 
    ${PROJECT_NAME}/sources/main.cpp
    ${PROJECT_NAME}/sources/window/window.cpp
    ${PROJECT_NAME}/sources/shader/shader_tools/shader_tools.cpp
    ${PROJECT_NAME}/sources/shader/shader.cpp
	${PROJECT_NAME}/sources/transform/transform.cpp
)
set(INCLUDE 
    ${PROJECT_NAME}/include/main.h
    ${PROJECT_NAME}/include/window/window.h
    ${PROJECT_NAME}/include/shader/shader_tools/shader_tools.h
    ${PROJECT_NAME}/include/shader/shader.h
	${PROJECT_NAME}/include/transform/transform.h
	${PROJECT_NAME}/include/transform/position.h
	${PROJECT_NAME}/include/transform/rotation.h
	${PROJECT_NAME}/include/transform/scale.h
	${PROJECT_NAME}/include/utils/error.h
	${PROJECT_NAME}/include/utils/stats.h
)
file(GLOB_RECURSE SHADERS
    ${PROJECT_NAME}/resources/shaders/*.glsl
)
file(GLOB_RECURSE IMAGES
    ${PROJECT_NAME}/resources/images/*
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SHADERS})

add_executable(${PROJECT_NAME} ${INCLUDE} ${SOURCES} ${SHADERS})

set_source_files_properties(${SHADERS} PROPERTIES HEADER_FILE_ONLY TRUE) #adds shaders to the editor but won't compile them

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries(${PROJECT_NAME} PRIVATE stb::stb)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${SHADERS}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_custom_command(
    TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${IMAGES}
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)
