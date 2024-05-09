//
// Created by m1504 on 24-5-9.
//
#include "Camera.h"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"

glm::vec3 CCamera::GetPosition() const {
    return Position;
}

glm::vec3 CCamera::GetFront() const {
    return GetDirection();
}

glm::vec3 CCamera::GetCameraUp() const {
    glm::mat4 RotationMatrix = glm::toMat4(glm::quat(Rotation));
    return {RotationMatrix * glm::vec4(CameraConstants::WorldUp, 0.0f)};
}

glm::vec3 CCamera::GetCameraRight() const {
    const glm::vec3 Front = GetFront();
    const glm::vec3 Up = GetCameraUp();
    return glm::normalize(glm::cross(Front, Up));
}

glm::quat CCamera::GetRotationQuaternion() const {
    return {glm::radians(Rotation)};
}

glm::quat CCamera::GetRotation() const {
    return Rotation;
}

glm::vec3 CCamera::GetDirection() const {
    glm::mat4 RotationMatrix = glm::toMat4(glm::quat(Rotation));
    return {RotationMatrix * glm::vec4(CameraConstants::WorldFront, 0.0f)};
}

glm::mat4 CCamera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + GetFront(), GetCameraUp());
}

void CCamera::ProcessMovementInput(const glm::vec3 InputDirection, float DeltaTime) {
    const glm::vec3 NormalizedDirection = glm::normalize(InputDirection);
    Position += NormalizedDirection * Speed * DeltaTime;
}

void CCamera::ProcessMouseMovement(float Yaw, float Pitch, FCameraRotationInputConfig CameraRotationInputConfig) {
    const float YawOffset = CameraRotationInputConfig.InvertYaw ? -Yaw : Yaw;
    const float PitchOffset = CameraRotationInputConfig.InvertPitch ? -Pitch : Pitch;
    AddYaw(YawOffset * Sensitivity);
    AddPitch(PitchOffset * Sensitivity);
}

void CCamera::ProcessMouseScroll(float DeltaZoom) {
    Zoom = glm::clamp(Zoom - DeltaZoom, 1.0f, 90.0f);
}

void CCamera::AddYaw(const float Yaw) {
    Rotation.z += Yaw;
    if(Rotation.z > 360.0f) {
        Rotation.z -= 360.0f;
    }
    else if(Rotation.z < -360.f) {
        Rotation.z += 360.0f;
    }
}

void CCamera::AddPitch(const float Pitch) {
    Rotation.y = glm::clamp(Rotation.y + Pitch, -89.0f, 89.0f);
}
