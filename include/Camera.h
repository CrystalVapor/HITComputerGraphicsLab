//
// Created by m1504 on 24-5-9.
//

#ifndef COMPUTERGRAPHICSLAB_CAMERA_H
#define COMPUTERGRAPHICSLAB_CAMERA_H

#include <Camera.h>


#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/detail/type_quat.hpp"

enum ECameraMovementInput {
    Forward = 0,
    Backward,
    Left,
    Right
};

namespace CameraConstants {
    constexpr float Speed = 2.5f;
    constexpr float Sensitivity = 0.2f;
    constexpr float Zoom = 45.0f;
    const glm::vec3 WorldFront(0.0f, 0.0f, -1.0f);
    const glm::vec3 WorldRight(1.0f, 0.0f, 0.0f);
    const glm::vec3 WorldUp(0.0f, 1.0f, 0.0f);
    const glm::vec3 MovementDirs[] = {
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f)
    };
}

struct FCameraRotationInputConfig{
    explicit FCameraRotationInputConfig(GLboolean InInvertYaw = false, GLboolean InInvertPitch = false):
    InvertYaw(InInvertYaw), InvertPitch(InInvertPitch) {};
    GLboolean InvertYaw = false;
    GLboolean InvertPitch = false;
};

class CCamera {
public:
    explicit CCamera(glm::vec3 InPosition = glm::vec3(0.f, 10.f, 0.0f),
            glm::vec3 InRotation = glm::vec3(0.0f, 0.0f, 0.0f),
            float InZoom = CameraConstants::Zoom,
            float InSpeed = CameraConstants::Speed,
            float InSensitivity = CameraConstants::Sensitivity)
    :Position(InPosition),
     Rotation(InRotation),
     Zoom(InZoom),
     Speed(InSpeed),
     Sensitivity(InSensitivity) {};

    glm::vec3 GetPosition() const;
    glm::vec3 GetCameraFront() const;
    glm::vec3 GetCameraUp() const;
    glm::vec3 GetCameraRight() const;

    glm::vec3 GetRotation() const;
    glm::vec3 GetRotationRadians() const;
    glm::vec3 GetDirection() const;
    glm::mat4 GetViewMatrix() const;

    glm::mat4 GetLocalToWorldMatrix() const;

    void ProcessMovementInput(glm::vec3 InputLocalDirection, float DeltaTime);
    void ProcessCameraRotation(float Yaw, float Pitch, FCameraRotationInputConfig CameraRotationInputConfig);
    void ProcessCameraZoom(float DeltaZoom);

    void AddYaw(float Yaw);
    void AddPitch(float Pitch);

    void LookAt(glm::vec3 Target);

    glm::vec3 Position;
    glm::vec3 Rotation/*In GLM, Euler rotation is Pitch Yaw and Roll*/;
    float Zoom;
    float Speed;
    float Sensitivity;
    float LastYaw = 0.0f;
    float LastPitch = 0.0f;
};


#endif //COMPUTERGRAPHICSLAB_CAMERA_H

