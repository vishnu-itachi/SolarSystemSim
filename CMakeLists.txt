# CMakeList.txt : CMake project for SolarSystemSim, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SolarSystemSim")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} "src/SolarSystemSim.cpp" "src/SolarSystemSim.h")

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)


# TODO: Add tests and install targets if needed.
