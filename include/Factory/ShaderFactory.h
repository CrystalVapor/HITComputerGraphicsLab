//
// Created by m1504 on 24-5-8.
//

#ifndef COMPUTERGRAPHICSLAB_SHADERFACTORY_H
#define COMPUTERGRAPHICSLAB_SHADERFACTORY_H

#include <memory>

class FShader;

class FShaderFactory {
public:
    static std::shared_ptr<FShader> CreateShader(const char* vertexPath, const char* fragmentPath);
};


#endif //COMPUTERGRAPHICSLAB_SHADERFACTORY_H
