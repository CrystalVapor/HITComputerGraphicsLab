cmake_minimum_required(VERSION 3.22)
project(ComputerGraphicsLab)

set(CMAKE_BUILD_TYPE Debug)

# 设定二进制输出目录
set(binary_dir ${CMAKE_SOURCE_DIR}/bin )
# 设定编译器
set(CMAKE_CXX_STANDARD 11)
# 设定Cmake输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${binary_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${binary_dir}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${binary_dir}/lib)

add_subdirectory(library)

include_directories(${GLFW3_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${STB_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(Factories src/Shader.cpp src/Factory/ShaderFactory.cpp
        src/Factory/TextureFactory.cpp
        include/Factory/TextureFactory.h
        src/Texture.cpp
        include/Texture.h)

add_executable(Lab1 src/Lab1.cpp
        src/LabWindow.cpp)
target_link_libraries(Lab1 glfw glad Factories)

add_executable(Lab2 src/Lab2.cpp src/Camera.cpp
        src/LabWindow.cpp
        src/LabWindow_WithCamera.cpp)
target_link_libraries(Lab2 glfw glad glm::glm Factories)

add_library(Window_Camera src/LabWindow.cpp src/Camera.cpp src/LabWindow_WithCamera.cpp)

add_executable(Lab3 src/Lab3.cpp
        src/LabWindow.cpp
        src/LabWindow_WithCamera.cpp
        src/Camera.cpp)
target_link_libraries(Lab3 glfw glad glm::glm Factories)

add_executable(Lab4 src/Lab4.cpp
        src/LabWindow.cpp
        src/LabWindow_WithCamera.cpp
        src/Camera.cpp)
target_link_libraries(Lab4 glfw glad glm::glm Factories)

include_directories(${Vulkan_INCLUDE_DIR})


add_executable(Lab5 src/Lab5.cpp
        src/LabWindow.cpp)
target_link_libraries(Lab5 glfw glad glm::glm Factories)
