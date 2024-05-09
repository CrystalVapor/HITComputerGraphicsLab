//
// Created by m1504 on 24-5-9.
//

#include "LabWindow.h"

#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

bool CLabWindow::bGLFWInitialized = false;

CLabWindow::~CLabWindow() {
    glfwTerminate();

}

void CLabWindow::Init() {
    if(!bGLFWInitialized) {
        LoadGLFW();
        bGLFWInitialized = true;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    LoadGLAD();
    glViewport(0, 0, width, height);
}

void CLabWindow::Begin() {
    while(!glfwWindowShouldClose(window)){
        ProcessInput();
        OnPaint();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void CLabWindow::OnPaint() {

}

void CLabWindow::Exit() {
}

void CLabWindow::ProcessInput() {

}

void CLabWindow::LoadGLFW() {
    glfwInit();
}

void CLabWindow::LoadGLAD() {
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}
