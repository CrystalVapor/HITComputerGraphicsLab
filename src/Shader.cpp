//
// Created by m1504 on 24-5-8.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

FShader::FShader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch(std::ifstream::failure &e){
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char *vertexCode_Exposed = vertexCode.c_str();
    const char *fragmentCode_Exposed = fragmentCode.c_str();
    unsigned int vertexShaderObj, fragmentShaderObj;
    int success = 1;
    char infoLog[512];

    vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObj, 1, &vertexCode_Exposed, nullptr);
    glCompileShader(vertexShaderObj);
    glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShaderObj, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObj, 1, &fragmentCode_Exposed, nullptr);
    glCompileShader(fragmentShaderObj);
    glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShaderObj, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShaderObj);
    glAttachShader(ID, fragmentShaderObj);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderObj);
    glDeleteShader(fragmentShaderObj);
}

FShader::FShader(const FShader &shader) {
    ID = shader.ID;
}

FShader &FShader::operator=(const FShader &shader) = default;

void FShader::SetIntParam(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void FShader::SetMat4Param(const std::string &name, const glm::mat4 & value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}



