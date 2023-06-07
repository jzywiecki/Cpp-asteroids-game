cmake_minimum_required(VERSION 3.21)
project(final_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(${PROJECT_NAME} main.cpp spaceship.cpp spaceship.h bullet.cpp bullet.h asteroid.cpp asteroid.h game.cpp game.h menu.cpp menu.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(final_project sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
