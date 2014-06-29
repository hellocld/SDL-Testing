cmake_minimum_required(VERSION 2.6)
project(SDL_Testing)

include_directories ("${PROJECT_SOURCE_DIR}/CLD-ECS"
	"${PROJECT_SOURCE_DIR}/Components" "${PROJECT_SOURCE_DIR}/Systems")

add_subdirectory (CLD-ECS)
add_subdirectory (Systems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable (SDL-Testing main.cxx)
target_link_libraries(SDL-Testing library world system factory render SDL2)
