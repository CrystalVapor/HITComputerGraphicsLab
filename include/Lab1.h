//
// Created by m1504 on 24-5-9.
//

#ifndef LAB1_H
#define LAB1_H
#include <LabWindow.h>
#include <memory>

class FShader;

class CLab1Window: public CLabWindow {
public:
    virtual void Begin() override;
    virtual void OnPaint() override;
    void SetShaderPath(const char* vertexPath, const char* fragmentPath);
protected:
    std::shared_ptr<FShader> shader;
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    const char* vertexPath = nullptr;
    const char* fragmentPath = nullptr;
};

#endif //LAB1_H
