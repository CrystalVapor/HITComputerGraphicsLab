//
// Created by m1504 on 24-5-25.
//

#include "LabWindow_WithCamera.h"

#include <Camera.h>

#include "GLFW/glfw3.h"

CLabWindow_WithCamera::CLabWindow_WithCamera() {
    Camera = std::make_shared<CCamera>();
    Camera->Position = glm::vec3(0.0f, 0.0f, 3.0f);
}

void CLabWindow_WithCamera::Begin() {
    CLabWindow::Begin();
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, OnMouseMoveCallback);
    glfwSetScrollCallback(window, OnMouseScrollCallback);
}

void CLabWindow_WithCamera::OnPaint() {
    CLabWindow::OnPaint();
    const auto CurrentFrameTime = static_cast<float>(glfwGetTime());
    DeltaTime = CurrentFrameTime - LastFrameTime;
    LastFrameTime = CurrentFrameTime;
}

void CLabWindow_WithCamera::ProcessInput() {
    CLabWindow::ProcessInput();
    glm::vec3 MovementInput(0.0f);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        MovementInput.z -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        MovementInput.z += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        MovementInput.x -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        MovementInput.x += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        MovementInput.y += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        MovementInput.y -= 1.0f;
    Camera->ProcessMovementInput(MovementInput, DeltaTime);
}

void CLabWindow_WithCamera::OnMouseMoveCallback(GLFWwindow *window, double xoffset, double yoffset) {
    void* UserPointer = glfwGetWindowUserPointer(window);
    if(UserPointer) {
        auto* Window = static_cast<CLabWindow_WithCamera *>(UserPointer);
        Window->OnMouseMove(xoffset, yoffset);
    }
}

void CLabWindow_WithCamera::OnMouseScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    void* UserPointer = glfwGetWindowUserPointer(window);
    if(UserPointer) {
        auto* Window = static_cast<CLabWindow_WithCamera *>(UserPointer);
        Window->OnMouseScroll(xoffset, yoffset);
    }
}

void CLabWindow_WithCamera::OnMouseScroll(double xoffset, double yoffset) {
    Camera->ProcessCameraZoom(static_cast<float>(yoffset));
}

void CLabWindow_WithCamera::OnMouseMove(double xoffset, double yoffset) {
    auto f_camera_rotation_input_config = FCameraRotationInputConfig(true, true);
    Camera->ProcessCameraRotation(xoffset, yoffset, f_camera_rotation_input_config);
}

void CLabWindow_WithCamera::SetModelMatrix(const glm::mat4 &InModelMatrix) {
    ModelMatrix = InModelMatrix;
}

glm::mat4 CLabWindow_WithCamera::GetCameraViewMatrix() {
    return Camera->GetViewMatrix();
}

glm::mat4 CLabWindow_WithCamera::GetProjectionMatrix() {
    return glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(width)/static_cast<float>(height),
            0.1f, 100.0f);
}

glm::mat4 CLabWindow_WithCamera::GetComposedCameraMatrix() {
    auto view = Camera->GetViewMatrix();
    auto projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(width)/static_cast<float>(height),
            0.1f, 100.0f);
    return projection * view * ModelMatrix;
}
