#pragma once
#include "nata.h"
#include "core/ecs/ecs.h"

#include "core/ecs/ECamera.hpp"
#include "core/ecs/EOurObject.hpp"
#include "core/ecs/EOurGameMode.hpp"

using namespace Nata;
using namespace glm;

float NTime::Time = 0.f;
float NTime::DeltaTime = 0.f;
NWindow* NEngine::Window = nullptr;
NInput* NEngine::Input = nullptr;
CCamera* NEngine::ActiveCamera = nullptr;
float NEngine::WindowSizeX = 700.f;
float NEngine::WindowSizeY = 500.f;

int main(int argc, char** argv)
{
    NWindow* win = new NWindow("OpenGL Studies", NEngine::WindowSizeX, NEngine::WindowSizeY);
    NRenderer* renderer = win->GetRenderer();
    NInput* input = win->GetInput();
    NWorld* world = new NWorld();
    NOurGameMode* gameMode = new NOurGameMode();
    world->SetGameMode(gameMode);
    ECamera* camera = world->Instantiate<ECamera>();

    NEngine::Window = win;
    NEngine::Input = input;
    NEngine::ActiveCamera = camera->Camera;

    glEnable(GL_DEPTH_TEST);

    float deltaTime = 0.f;
    double lastFrame = 0.f;

    world->Begin();
    while (!win->Closed())
    {
        win->Clear();

        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        NTime::Time = (float)glfwGetTime();
        NTime::DeltaTime = deltaTime;

        world->Tick(deltaTime);
        win->Update();
    }
}