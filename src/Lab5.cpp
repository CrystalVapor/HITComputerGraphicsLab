//
// Created by m1504 on 24-6-15.
//

#include "Lab5.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "../library/glfw/src/internal.h"
#include "glm/gtc/random.hpp"

int main(int argc, char** argv) {
    CLab5Window Window;
    Window.Init();
    Window.Run();
    return 0;
}

FRectangle::FRectangle(const glm::vec2 &Position, float Width, float Height):
    Position(Position),
    Width(Width),
    Height(Height)
{
}

FRectangle::~FRectangle() {
    if(RenderDataInitialized) {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }
}

bool FRectangle::operator&(const FRectangle &Other) const {
    // is this rectangle colliding with other rectangle
    const float HalfWidth = Width/2;
    const float HalfHeight = Height/2;
    const float OtherHalfWidth = Other.Width/2;
    const float OtherHalfHeight = Other.Height/2;
    return Position.x - HalfWidth < Other.Position.x + OtherHalfWidth &&
           Position.x + HalfWidth > Other.Position.x - OtherHalfWidth &&
           Position.y - HalfHeight < Other.Position.y + OtherHalfHeight &&
           Position.y + HalfHeight > Other.Position.y - OtherHalfHeight;
}

std::vector<glm::vec2> FRectangle::ToVertices() const {
    const float AbsoluteWidth = Width/GameConstants::Window_Width;
    const float AbsoluteHeight = Height/GameConstants::Window_Height;
    const float AbsoluteX = Position.x/GameConstants::Window_Width;
    const float AbsoluteY = Position.y/GameConstants::Window_Height;
    const float HalfAbsoluteWidth = AbsoluteWidth/2;
    const float HalfAbsoluteHeight = AbsoluteHeight/2;
    return {
            {AbsoluteX - HalfAbsoluteWidth, AbsoluteY + HalfAbsoluteHeight},
            {AbsoluteX - HalfAbsoluteWidth, AbsoluteY - HalfAbsoluteHeight},
            {AbsoluteX + HalfAbsoluteWidth, AbsoluteY - HalfAbsoluteHeight},
            {AbsoluteX + HalfAbsoluteWidth, AbsoluteY + HalfAbsoluteHeight}
    };
}

void FRectangle::InitRenderData() {
    auto Vertices = ToVertices();
    float VerticesArray[] = {
            Vertices[0].x, Vertices[0].y, 0.0f, 1.0f,
            Vertices[1].x, Vertices[1].y, 0.0f, 0.0f,
            Vertices[2].x, Vertices[2].y, 1.0f, 0.0f,
            Vertices[3].x, Vertices[3].y, 1.0f, 1.0f
    };
    uint32_t Indices[] = {
            0, 1, 3,
            1, 2, 3
    };
    if(!RenderDataInitialized) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VerticesArray), VerticesArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    RenderDataInitialized = true;
}

Tube::Tube(float GapAt, float DistanceFromOrigin): GapAt(GapAt), DistanceFromOrigin(DistanceFromOrigin){
}

std::vector<FRectangle> Tube::GetTubeRectangles() const {
    std::vector<FRectangle> Rects;
    /*Rects.push_back({{DistanceFromOrigin, (GapAt - GameConstants::Gap_Size/2)/2},
        GameConstants::Tube_Width, GapAt - GameConstants::Gap_Size/2});
    const float GapTop = GapAt + GameConstants::Gap_Size/2;
    Rects.push_back({{DistanceFromOrigin, (GameConstants::Window_Height - GapTop)/2 + GapTop},
        GameConstants::Tube_Width, GameConstants::Window_Height - GapTop});*/
    Rects.push_back({{DistanceFromOrigin-GameConstants::Tube_Width/2,
            GapAt-GameConstants::Gap_Size/2},
        {DistanceFromOrigin+GameConstants::Tube_Width/2,
            -GameConstants::Window_Height/2}});
    Rects.push_back({{DistanceFromOrigin-GameConstants::Tube_Width/2,
            GameConstants::Window_Height/2},
        {DistanceFromOrigin+GameConstants::Tube_Width/2,
            GapAt+GameConstants::Gap_Size/2}});
    return Rects;
}


void CLab5Window::OnPaint() {
    CLabWindow::OnPaint();
    glClearColor(0.2f,0.3f,0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    float CurrentTime = glfwGetTime();
    float DeltaTime = CurrentTime - LastFrameTime;
    LastFrameTime = CurrentTime;
    glm::vec2 PlayerViewPoint = {Player.x, 0};
    PlayerRectangle = {{Player.x - GameConstants::Player_Width/2, Player.y - GameConstants::Player_Height/2},
        GameConstants::Player_Width, GameConstants::Player_Height};
    TubesRectangles.clear();
    for(auto& Tube:Tubes) {
        auto Rectangles = Tube.GetTubeRectangles();
        for(auto& Rectangle:Rectangles) {
            TubesRectangles.push_back(Rectangle);
        }
    }
    Tick(DeltaTime);
    glUseProgram(TubeShader->ID);
    for(auto& Rectangle:TubesRectangles){
        FRectangle RebasedRectangle = Rectangle.RebaseOrigin(PlayerViewPoint);
        RebasedRectangle.InitRenderData();
        glBindVertexArray(RebasedRectangle.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RebasedRectangle.EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glUseProgram(PlayerShader->ID);
    PlayerRectangle.Position.x = 0;
    PlayerRectangle.InitRenderData();
    glBindVertexArray(PlayerRectangle.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PlayerRectangle.EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void CLab5Window::Begin() {
    CLabWindow::Begin();
    TubeShader = new FShader("res/Shaders/Vertex/Tube.glsl", "res/Shaders/Fragment/Tube.glsl");
    PlayerShader = new FShader("res/Shaders/Vertex/Player.glsl", "res/Shaders/Fragment/Player.glsl");
    InitTubes();
}

void CLab5Window::Init() {
    CLabWindow::Init();
}

void CLab5Window::ProcessInput() {
    CLabWindow::ProcessInput();
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS) {
        if(!bGameStarted) {
            bGameStarted = true;
        }
        bJumpPressed = true;
    }else {
        bJumpPressed = false;
        bPlayerJumping = false;
    }
}

void CLab5Window::InitTubes() {
    Tubes.clear();
    Tubes.push_back({0, 350});
}

void CLab5Window::GenNewTube() {
    const auto linear_rand = glm::linearRand<float>(0,1);
    const float NextTubeX = Tubes.back().DistanceFromOrigin + GameConstants::Tube_Distance;
    const float RawNextTubeGap = (GameConstants::Window_Height-GameConstants::Gap_Size)*linear_rand;
    const float NextTubeGap = GameConstants::Window_Height/2 - GameConstants::Gap_Size/2 - RawNextTubeGap;
    Tubes.push_back({NextTubeGap, NextTubeX});
}

void CLab5Window::GameOver() {
    std::cout << "Game Over" << std::endl;
    bGameStarted = false;
    Player = {0,0};
    PlayerVerticalSpeed = 0;
    InitTubes();
}

void CLab5Window::Tick(float DeltaTime) {
    if(!bGameStarted) {
        return;
    }
    if(bJumpPressed&&!bPlayerJumping) {
        PlayerVerticalSpeed = GameConstants::Player_Jump_Speed;
        bPlayerJumping = true;
    }
    PlayerVerticalSpeed -= GameConstants::Gravity*DeltaTime;
    Player.y += PlayerVerticalSpeed*DeltaTime;

    Player.x += GameConstants::Player_Horizonal_Speed*DeltaTime;

    if(Player.y<-300) {
        GameOver();
    }

    for(auto& TubeRect:TubesRectangles) {
        if(PlayerRectangle&TubeRect) {
            GameOver();
        }
    }

    if(Player.x>((long long)Tubes.size()-5)*GameConstants::Tube_Distance) {
        GenNewTube();
    }
}