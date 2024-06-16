//
// Created by m1504 on 24-6-15.
//

#ifndef LAB5_H
#define LAB5_H

#include <LabWindow.h>
#include <vector>
#include <glm/glm.hpp>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

class FShader;

namespace GameConstants {
    float Window_Width = 800.0f;
    float Window_Height = 600.0f;
    float Player_Width = 50.0f;
    float Player_Height = 50.0f;
    float Tube_Width = 50.0f;
    float Gap_Size = 220.0f;
    float Player_Jump_Speed = 150.0f;

    float Tube_Distance = 350.0f;

    float Player_Horizonal_Speed = 100.0f;

    float Gravity = 400.f;

    glm::mat4 OrthoMatrix = glm::ortho(0.0f, Window_Width, 0.0f, Window_Height);

}

class FRectangle {
public:
    FRectangle() = default;
    FRectangle(const glm::vec2& Position, float Width, float Height);
    FRectangle(const glm::vec2& LeftTop, const glm::vec2& RightBottom):
        Position({LeftTop.x+(RightBottom.x-LeftTop.x)/2, LeftTop.y+(RightBottom.y-LeftTop.y)/2}),
        Width(RightBottom.x - LeftTop.x),
        Height(LeftTop.y - RightBottom.y)
    {
    }
    virtual ~FRectangle();
    // is this rectangle colliding with other rectangle
    bool operator&(const FRectangle& Other) const;

    std::vector<glm::vec2> ToVertices() const;

    FRectangle PannedBy(const glm::vec2& Delta) const {
        return {Position + Delta, Width, Height};
    }

    FRectangle RebaseOrigin(const glm::vec2& NewOrigin) const {
        return {Position - NewOrigin, Width, Height};
    }

    void InitRenderData();
    glm::vec2 Position;
    float Width;
    float Height;
    uint32_t VAO, VBO, EBO;
    bool RenderDataInitialized = false;
};

class Tube {
public:
    Tube() = default;
    Tube(float GapAt, float DistanceFromOrigin);
    std::vector<FRectangle> GetTubeRectangles() const;

    float GapAt = 0.f;
    float DistanceFromOrigin = 0.f;
};

class CLab5Window: public CLabWindow {
public:
    CLab5Window() = default;
    virtual void OnPaint() override;
    virtual void Begin() override;
    virtual void Init() override;
    virtual void ProcessInput() override;

    void InitTubes();
    void GenNewTube();

    void GameOver();

    virtual void Tick(float DeltaTime);

    glm::mat4 GetAspectMatrix() const {
        return glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, GameConstants::Window_Height / GameConstants::Window_Width, 1.0f));
    }

    bool bPlayerJumping = false;
    bool bJumpPressed = false;

    float LastFrameTime = 0.0f;
    float DeltaTime = 0.0f;

    glm::vec2 Player = {0,0};
    FRectangle PlayerRectangle;
    float PlayerVerticalSpeed = 0.0f;
    std::vector<Tube> Tubes;
    std::vector<FRectangle> TubesRectangles;

    float Score = 0.0f;
    float LastJumpTime = 0.0f;

    FShader* TubeShader;
    FShader* PlayerShader;

    bool bGameStarted = false;
};


#endif //LAB5_H
