//
// Created by m1504 on 24-5-25.
//

#ifndef LABWINDOW_WITHCAMERA_H
#define LABWINDOW_WITHCAMERA_H
#include <LabWindow.h>
#include <memory>

#include "glm/glm.hpp"

class CCamera;

class CLabWindow_WithCamera: public CLabWindow {
public:
    CLabWindow_WithCamera();
    virtual void Begin() override;
    virtual void OnPaint() override;
protected:
    virtual void ProcessInput() override;
    virtual void OnMouseScroll(double xoffset, double yoffset);
    virtual void OnMouseMove(double xoffset, double yoffset);
    virtual void SetModelMatrix(const glm::mat4& InModelMatrix);
    virtual glm::mat4 GetCameraViewMatrix();
    virtual glm::mat4 GetProjectionMatrix();
    virtual glm::mat4 GetComposedCameraMatrix();

    std::shared_ptr<CCamera> Camera;
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    float DeltaTime = 0.0f;
    float LastFrameTime = 0.0f;
private:
    static void OnMouseMoveCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif //LABWINDOW_WITHCAMERA_H
