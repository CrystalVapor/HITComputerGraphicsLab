//
// Created by m1504 on 24-5-9.
//
#include "Lab2.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include "Factory/ShaderFactory.h"
#include "Factory/TextureFactory.h"
#include "glm/vec3.hpp"
#include "Camera.h"

CLab2Window* CLab2Window::Instance = nullptr;

int main(int argc, char *argv[]){
    CLab2Window window;
    window.Init();
    window.Begin();
    window.Exit();
    return 0;
}

void CLab2Window::Init() {
    if(!Instance)
        Instance = this;
    CLabWindow::Init();
    Camera = std::make_shared<CCamera>(glm::vec3(0.0f, 10.f, 0.0f));

    float DiamondVertices[] = {
            // vertex coords    // texture coords
             0.5f,  0.0f,  0.0f,   0.0f, 0.0f,
             0.0f,  0.5f,  0.0f,   1.0f, 0.0f,
             0.0f,  0.0f,  0.5f,   1.0f, 1.0f,
            -0.5f,  0.0f,  0.0f,   0.0f, 0.0f,
             0.0f, -0.5f,  0.0f,   1.0f, 0.0f,
             0.0f,  0.0f, -0.5f,   1.0f, 1.0f
    };
    unsigned int DiamondIndices[] = {
            2, 0, 1,
            3, 1, 2,
            4, 3, 2,
            0, 4, 2,
            4, 0, 5,
            0, 1, 5,
            1, 3, 5,
            3, 4, 5,
    };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, &DiamondVAO);
    glGenBuffers(1, &DiamondVBO);
    glGenBuffers(1, &DiamondEBO);
    glBindVertexArray(DiamondVAO);
    glBindBuffer(GL_ARRAY_BUFFER, DiamondVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(DiamondVertices), DiamondVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DiamondEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(DiamondIndices), DiamondIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    DiamondShader = FShaderFactory::CreateShader("res/Shaders/Vertex/diamondVertex.glsl", "res/Shaders/Fragment/diamondFragment.glsl");
    DiamondTexture = FTextureFactory::CreateTexture("res/Textures/diamondTexture.jpg");

}

void CLab2Window::OnPaint() {
    CLabWindow::OnPaint();
    const auto CurrentFrameTime = static_cast<float>(glfwGetTime());
    DeltaTime = CurrentFrameTime - LastFrameTime;
    LastFrameTime = CurrentFrameTime;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, DiamondTexture->ID);
    glClearColor(0.2f,0.3f,0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(DiamondShader->ID);
    //DiamondShader->SetMat4Param("model", glm::mat4(1.0f));
    //DiamondShader->SetMat4Param("view", Camera->GetViewMatrix());
    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(width)/static_cast<float>(height),
            0.1f, 100.0f);
    DiamondShader->SetMat4Param("model", model);
    DiamondShader->SetMat4Param("view", view);
    DiamondShader->SetMat4Param("projection", projection);
    glBindVertexArray(DiamondVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, DiamondEBO);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CLab2Window::Begin() {
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetScrollCallback(window, OnMouseScroll);
    glUseProgram(DiamondShader->ID);
    CLabWindow::Begin();
}

void CLab2Window::ProcessInput() {
    CLabWindow::ProcessInput();
    glm::vec3 MovementInput(0.0f);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        MovementInput.z += 1.0f;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        MovementInput.z -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        MovementInput.x -= 1.0f;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        MovementInput.x += 1.0f;
    Camera->ProcessMovementInput(MovementInput, DeltaTime);
}

void CLab2Window::Exit() {
    CLabWindow::Exit();
}

void CLab2Window::OnMouseMove(GLFWwindow *Window, double xpos, double ypos) {
    auto f_camera_rotation_input_config = FCameraRotationInputConfig(false, true);
    Instance->Camera->ProcessCameraRotation(xpos, ypos, f_camera_rotation_input_config);
}

void CLab2Window::OnMouseScroll(GLFWwindow *Window, double xoffset, double yoffset) {
    Instance->Camera->ProcessCameraZoom(static_cast<float>(yoffset));
}
