//
// Created by m1504 on 24-5-9.
//
#include "Camera.h"

#include <cstdio>

#include "glm/ext.hpp"

glm::vec3 CCamera::GetPosition() const {
    return Position;
}

glm::vec3 CCamera::GetCameraFront() const {
    return GetDirection();
}

glm::vec3 CCamera::GetCameraUp() const {
    glm::mat4 RotationMatrix = static_cast<glm::mat4>(glm::quat(GetRotationRadians()));
    return {RotationMatrix * glm::vec4(CameraConstants::WorldUp, 0.0f)};
}

glm::vec3 CCamera::GetCameraRight() const {
    const glm::vec3 Front = GetCameraFront();
    const glm::vec3 Up = GetCameraUp();
    return glm::normalize(glm::cross(Front, Up));
}

glm::vec3 CCamera::GetRotation() const {
    return Rotation;
}

glm::vec3 CCamera::GetRotationRadians() const {
    return glm::radians(Rotation);
}

glm::vec3 CCamera::GetDirection() const {
    auto RotationMatrix = static_cast<glm::mat4>(glm::quat(GetRotationRadians()));
    return {RotationMatrix * glm::vec4(CameraConstants::WorldFront, 1.0f)};
}

glm::mat4 CCamera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + GetCameraFront(), GetCameraUp());
}

glm::mat4 CCamera::GetLocalToWorldMatrix() const {
    return static_cast<glm::mat4>(glm::quat(GetRotationRadians()));
}

void CCamera::ProcessMovementInput(const glm::vec3 InputLocalDirection, float DeltaTime) {
    if(InputLocalDirection == glm::vec3(0.0f) || DeltaTime == 0.0f) {
        return;
    }
    const glm::vec3 NormalizedDirection = glm::normalize(InputLocalDirection);
    const glm::vec3 WorldDirection = GetLocalToWorldMatrix() * glm::vec4(NormalizedDirection, 0.f);
    Position += WorldDirection * Speed * DeltaTime;
}

void CCamera::ProcessCameraRotation(float Yaw, float Pitch, FCameraRotationInputConfig CameraRotationInputConfig) {
    const float rDeltaYaw = Yaw-LastYaw;
    const float rDeltaPitch = Pitch-LastPitch;
    LastPitch = Pitch;
    LastYaw = Yaw;
    const float deltaYaw = CameraRotationInputConfig.InvertYaw ? -rDeltaYaw : rDeltaYaw;
    const float deltaPitch = CameraRotationInputConfig.InvertPitch ? -rDeltaPitch : rDeltaPitch;
    AddYaw(deltaYaw * Sensitivity);
    AddPitch(deltaPitch * Sensitivity);
}

void CCamera::ProcessCameraZoom(float DeltaZoom) {
    Zoom = glm::clamp(Zoom - DeltaZoom, 1.0f, 90.0f);
}

void CCamera::AddYaw(const float Yaw) {
    float& y = Rotation.y;
    y += Yaw;
    if(y > 360.0f) {
        y -= 360.0f;
    }
    else if(y < -360.f) {
        y += 360.0f;
    }
}

void CCamera::AddPitch(const float Pitch) {
    float& p = Rotation.x;
    p = glm::clamp(p + Pitch, -89.0f, 89.0f);
}
