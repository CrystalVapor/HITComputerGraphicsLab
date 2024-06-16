add_subdirectory(glfw)
set(GLFW3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include PARENT_SCOPE)

add_subdirectory(glad-gl3.3)
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glad-gl3.3/include PARENT_SCOPE)

option(GLM_BUILD_TESTS OFF)
add_subdirectory(glm)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glm PARENT_SCOPE)

set(STB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stb PARENT_SCOPE)

add_subdirectory(Vulkan-Headers)
set(VULKAN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Headers/include PARENT_SCOPE)