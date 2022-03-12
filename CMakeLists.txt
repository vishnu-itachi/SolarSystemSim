# CMakeList.txt : CMake project for SolarSystemSim, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
project ("SolarSystemSim")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
				"src/SolarSystemSim.cpp" 
				"src/SolarSystemSim.h" 
				"src/Renderer.h" 
				"src/Renderer.cpp" 
				"src/VertexBuffer.h" 
				"src/VertexBuffer.cpp"
				"src/IndexBuffer.h"
				"src/IndexBuffer.cpp" 
				"src/Shader.cpp" 
				"src/Shader.h" "Dependencies/GLEW/include/GL/GLU.h")


# find_package(GLEW REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
# find_package(glfw3 CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

SET(OPENGL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/include ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/include)
SET(OPENGL_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/lib/glew32s.lib ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLEW/lib/GLU32.lib ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/GLFW/lib-v2022/glfw3.lib Opengl32)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

# TODO: Add tests and install targets if needed.
