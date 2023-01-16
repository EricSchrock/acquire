cmake_minimum_required(VERSION 3.7)

project(acquire)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(SOURCES src/main.cpp src/Controller.cpp src/Game.cpp src/Renderer.cpp)

include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
