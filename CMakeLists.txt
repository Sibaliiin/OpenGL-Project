cmake_minimum_required(VERSION 3.10)

project(p C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(p
	src/main.c
	src/glad.c
)

target_include_directories(p PRIVATE
	include
)

target_link_libraries(p PRIVATE
	glfw
	OpenGL::GL
)
