//
// Created by m1504 on 24-5-26.
//

#include "Lab4.h"

#include <iostream>
#include <ostream>
#include <Shader.h>
#include <Factory/ShaderFactory.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    CLab4Window window;
    window.Init();
    window.Run();
    return 0;
}

void CLab4Window::Init() {
    CLabWindow::Init();
     float quadVertices[] = {
    // positions // texture Coords
    -1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
    1.0f, -1.0f, 0.0f,   1.0f, 0.0f };
    glGenVertexArrays(1, &VertexArrayObject);
    glGenBuffers(1, &ArrayBufferObject);
    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // this will unbind the VAO
    glBindVertexArray(0);

    glGenFramebuffers(1, &FrameBufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferObject);
    glGenTextures(1, &TextureBufferObject);
    glBindTexture(GL_TEXTURE_2D, TextureBufferObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TextureBufferObject, 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    FrameBufferShader = FShaderFactory::CreateShader("res/Shaders/Vertex/lab4.glsl","res/Shaders/Fragment/lab4.glsl");
    DefaultShader = FShaderFactory::CreateShader("res/Shaders/Vertex/lab4.glsl","res/Shaders/Fragment/Lab4FrameBuffer.glsl");
}

void CLab4Window::OnPaint() {
    CLabWindow::OnPaint();
    glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferObject);
    glClearColor(0.5f,0.5f,0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    FrameBufferShader->Activate();
    FrameBufferShader->SetIntParam("WindowWidth",width );
    FrameBufferShader->SetIntParam("WindowHeight",height );
    glBindVertexArray(VertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.5f,0.5f,0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DefaultShader->Activate();
    glBindVertexArray(VertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

