cmake_minimum_required(VERSION 2.6)
project(SDL_Testing)

include_directories ("${PROJECT_SOURCE_DIR}/CLD-ECS"
	"${PROJECT_SOURCE_DIR}/Components" "${PROJECT_SOURCE_DIR}/Systems"
	"${PROJECT_SOURCE_DIR}/CLD-Util"
	"${PROJECT_SOURCE_DIR}/CLD-Util/Collision")

add_subdirectory (CLD-ECS)
add_subdirectory (CLD-Util)
add_subdirectory (CLD-Util/Collision)
add_subdirectory (Systems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

add_executable (SDL-Testing main.cxx)
target_link_libraries(SDL-Testing library world system 
	physicsEngine input factory render collision-aabb SDL2)
