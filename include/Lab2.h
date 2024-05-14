//
// Created by m1504 on 24-5-9.
//

#ifndef LAB2_H
#define LAB2_H

#include <Camera.h>
#include <memory>

#include "LabWindow.h"

class FTexture;
class FShader;
class CCamera;

class CLab2Window: public CLabWindow {
public:
    virtual void Init() override;
    virtual void OnPaint() override;
    virtual void Begin() override;
    virtual void ProcessInput() override;
    virtual void Exit() override;
    static void OnMouseMove(GLFWwindow* Window, double xpos, double ypos);
    static void OnMouseScroll(GLFWwindow* Window, double xoffset, double yoffset);
protected:
    // call back cannot be a member function
    // we use singleton pattern to solve this problem
    // TODO: rewrite this by making the GLFWwindow* a morhism class
    static CLab2Window* Instance;
    std::shared_ptr<CCamera> Camera;

    std::shared_ptr<FShader> DiamondShader;
    std::shared_ptr<FTexture> DiamondTexture;

    unsigned int DiamondVAO = 0;
    unsigned int DiamondVBO = 0;
    unsigned int DiamondEBO = 0;
    float DeltaTime = 0.0f;
    float LastFrameTime = 0.0f;
};

#endif //LAB2_H
