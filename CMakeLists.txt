cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME SpaceShooter)
project(${PROJECT_NAME})

source_group("Shaders" FILES 
			"${CMAKE_SOURCE_DIR}/resources/shaders/vertShader.txt"
			"${CMAKE_SOURCE_DIR}/resources/shaders/fragShader.txt")

add_executable(${PROJECT_NAME}
			src/main.cpp
			src/Renderer/ShaderProgram.h
			src/Renderer/ShaderProgram.cpp
			src/Resources/ResourceManager.h
			src/Resources/ResourceManager.cpp

			resources/shaders/vertShader.txt
			resources/shaders/fragShader.txt)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)