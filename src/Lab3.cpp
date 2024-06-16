
//
// Created by m1504 on 24-5-20.
//

#include "Lab3.h"

#include "Texture.h"
#include "Factory/TextureFactory.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Texture.h"
#include "Factory/ShaderFactory.h"
#include "Factory/TextureFactory.h"
#include "glm/vec3.hpp"
#include "Camera.h"

int main(int argc, char *argv[]){
    CLab3Window window;
    window.Init();
    window.Run();
    return 0;
}

CLab3Window::CLab3Window() {
}

void CLab3Window::Init() {
    CLabWindow_WithCamera::Init();
    Camera->Sensitivity = 0.5f;
    float cubeVertices[] = {
    // positions          // texture coords // normals
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,     1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,     0.0f, 0.0f, -1.0f,

    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 1.0f,     0.0f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.5f,       1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f,       1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,

    0.5f, -0.5f, -0.5f,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f,      0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 0.0f,     1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,     1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, 0.5f,      1.0f, 0.0f,     0.0f, -1.0f, 0.0f,

    0.5f, -0.5f, 0.5f,      1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f,

    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f,      1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f,       1.0f, 0.0f,     0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f,       1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f,      0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,     0.0f, 1.0f, 0.0f

    };
    glGenVertexArrays(1, &VertexArray);
    glGenBuffers(1, &ArrayBuffer);
    glBindVertexArray(VertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

    Texture  = FTextureFactory::CreateTexture("res/Textures/diamondTexture.jpg");
    Shader = FShaderFactory::CreateShader("res/Shaders/Vertex/lab3vertex.glsl"
        , "res/Shaders/Fragment/phongLight.glsl");
}

void CLab3Window::ProcessInput() {
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        Camera->LookAt(glm::vec3(0.0, 0.0,0.0));
    }
    CLabWindow_WithCamera::ProcessInput();

}

void CLab3Window::OnPaint() {
    CLabWindow_WithCamera::OnPaint();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture->ID);
    glClearColor(0.1f,0.1f,0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Shader->Activate();
    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto projection = glm::mat4(1.0f);
    view = Camera->GetViewMatrix();
    auto rot = Camera->GetRotation();
    auto dir = Camera->GetDirection();
    projection = glm::perspective(
            glm::radians(45.0f),
            static_cast<float>(width)/static_cast<float>(height),
            0.1f, 100.0f);
    Shader->SetMat4Param("model", model);
    Shader->SetMat4Param("view", view);
    Shader->SetMat4Param("projection", projection);
    Shader->SetVec3Param("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader->SetVec3Param("lightPos", glm::vec3(0.0f, 4.0f, -3.0f));
    Shader->SetVec3Param("viewPos", Camera->GetPosition());
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
