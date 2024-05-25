//
// Created by m1504 on 24-5-20.
//

#ifndef LAB3_H
#define LAB3_H

#include <memory>
#include "LabWindow_WithCamera.h"

class FShader;
class FTexture;

class CLab3Window : public CLabWindow_WithCamera{
public:
    CLab3Window();
    virtual void Init() override;
    virtual void ProcessInput() override;
protected:
    virtual void OnPaint() override;
    std::shared_ptr<FTexture> Texture = nullptr;
    std::shared_ptr<FShader> Shader = nullptr;
    unsigned int VertexArray = 0;
    unsigned int ArrayBuffer = 0;
};

#endif //LAB3_H
