//
// Created by m1504 on 24-5-26.
//

#ifndef LAB4_H
#define LAB4_H
#include <memory>

#include "LabWindow.h"

class FShader;

class CLab4Window: public CLabWindow {
public:
    virtual void Init() override;
    virtual void OnPaint() override;
private:
    std::shared_ptr<FShader> FrameBufferShader;
    std::shared_ptr<FShader> DefaultShader;
    unsigned int VertexArrayObject = 0;
    unsigned int ArrayBufferObject = 0;
    unsigned int FrameBufferObject = 0;
    unsigned int TextureBufferObject = 0;
};

#endif //LAB4_H
