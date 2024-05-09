#include "Lab1.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Factory/ShaderFactory.h"

int main(int argc, char *argv[]){
    if(argc!=3){
        std::cerr << "Usage: " << argv[0] << " [vertex shader path] [fragment shader path]" << std::endl;
        return -1;
    }
    CLab1Window window;
    window.SetShaderPath(argv[1], argv[2]);
    window.Init();
    window.Begin();
    window.Exit();
    return 0;
}

void CLab1Window::Begin() {
    shader = FShaderFactory::CreateShader(vertexPath, fragmentPath);
    // alloc and bind vertex array to context
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // alloc and bind buffer to context
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // set render data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f};

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices),
                 vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3,
                          GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    CLabWindow::Begin();
}
void CLab1Window::OnPaint() {
    CLabWindow::OnPaint();
    glClearColor(0.2f,0.3f,0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader->ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CLab1Window::SetShaderPath(const char *InVertexPath, const char *InFragmentPath) {
    vertexPath = InVertexPath;
    fragmentPath = InFragmentPath;
}
