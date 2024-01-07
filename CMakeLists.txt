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
set(SHADERS
	${PROJECT_NAME}/resources/shaders/frag.glsl
	${PROJECT_NAME}/resources/shaders/vert.glsl
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${INCLUDE})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SHADERS})

add_executable(${PROJECT_NAME} ${INCLUDE} ${SOURCES} ${SHADERS})

set_source_files_properties(${SHADERS} PROPERTIES HEADER_FILE_ONLY TRUE)#adds shaders to the editor but won't compile them

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

foreach(file ${SHADERS})
	add_custom_command(
		TARGET ${PROJECT_NAME} PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/${file}
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endforeach()

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)
