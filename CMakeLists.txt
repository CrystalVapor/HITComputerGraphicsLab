cmake_minimum_required(VERSION 3.22)
project(ComputerGraphicsLab)

set(binary_dir ${CMAKE_SOURCE_DIR}/bin )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${binary_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${binary_dir}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${binary_dir}/lib)

find_package(OpenGL REQUIRED)
#find(GLUT REQUIRED)

add_executable(ComputerGraphicsLab main.cpp)
