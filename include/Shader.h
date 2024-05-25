//
// Created by Crystal on 24-5-8.
//

#ifndef COMPUTERGRAPHICSLAB_SHADER_H
#define COMPUTERGRAPHICSLAB_SHADER_H
#include "glm/fwd.hpp"

typedef unsigned int FShader_I;
class FShader {
    friend class FShaderFactory;
public:
    FShader_I ID;
    FShader(const FShader& shader);
    FShader& operator=(const FShader& shader);
    FShader(const char* vertexPath, const char* fragmentPath);

    void Activate() const;

    void SetIntParam(const std::string& name, int value) const;
    void SetMat4Param(const std::string& name, const glm::mat4 & value) const;
    void SetVec3Param(const std::string& name, const glm::vec3 & value) const;
};


#endif //COMPUTERGRAPHICSLAB_SHADER_H
