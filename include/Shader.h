//
// Created by Crystal on 24-5-8.
//

#ifndef COMPUTERGRAPHICSLAB_SHADER_H
#define COMPUTERGRAPHICSLAB_SHADER_H

typedef unsigned int FShader_I;
class FShader {
    friend class FShaderFactory;
public:
    FShader_I ID;
    FShader(const FShader& shader);
    FShader& operator=(const FShader& shader);
protected:
    FShader(const char* vertexPath, const char* fragmentPath);
};


#endif //COMPUTERGRAPHICSLAB_SHADER_H
