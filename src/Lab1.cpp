#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Factory/ShaderFactory.h"

typedef unsigned int FGLBuffer_I;
typedef unsigned int FGLVertexArray_I;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void onRender(FGLVertexArray_I vertexArrayObj, const std::shared_ptr<FShader> &shader);

int main(int argc, char *argv[]){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH,
                                          SCR_HEIGHT,
                                          "LearnOpenGL",
                                          nullptr,
                                          nullptr);
    if(window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // alloc and bind vertex array to context
    FGLVertexArray_I vertexArrayObj;
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);

    // alloc and bind buffer to context
    FGLBuffer_I vertexBufferObj;
    glGenBuffers(1, &vertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

    // set render data
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(vertices),
                 vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3,
                          GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // create shader
    auto shader = FShaderFactory::CreateShader("../res/Shaders/Vertex/lab1_vertex.glsl",
                                               "../res/Shaders/Fragment/lab1_fragment.glsl");



    // create window and call render loop
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f,0.3f,0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        onRender(vertexArrayObj, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void onRender(FGLVertexArray_I vertexArrayObj, const std::shared_ptr<FShader> &shader) {
    glUseProgram(shader->ID);
    glBindVertexArray(vertexArrayObj);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
