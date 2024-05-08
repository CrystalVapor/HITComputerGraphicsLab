//
// Created by m1504 on 24-5-8.
//

#include "Factory/ShaderFactory.h"

#include "Shader.h"

std::shared_ptr<FShader> FShaderFactory::CreateShader(const char *vertexPath, const char *fragmentPath) {
    // we simply call its constructor
    // since there's no morphism in shader class
    return std::shared_ptr<FShader>(new FShader(vertexPath, fragmentPath));
}
