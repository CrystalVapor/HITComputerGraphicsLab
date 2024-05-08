cmake_minimum_required(VERSION 3.22)
project(ComputerGraphicsLab)

# �趨���������Ŀ¼
set(binary_dir ${CMAKE_SOURCE_DIR}/bin )
# �趨������
set(CMAKE_CXX_STANDARD 11)
# �趨Cmake���Ŀ¼
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${binary_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${binary_dir}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${binary_dir}/lib)

add_subdirectory(library)

include_directories(${GLFW3_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Lab1 src/Lab1.cpp
        src/Shader.cpp
        src/Factory/ShaderFactory.cpp)
target_link_libraries(Lab1 glfw glad)