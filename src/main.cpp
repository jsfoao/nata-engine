#pragma once
#include "nata.h"
#include "exercises/exercises.hpp"
#include "core/ecs/ecs.h"

#include "core/ecs/test_entity.hpp"
#include "core/ecs/test_gamemode.hpp"
#include "core/ecs/transform_comp.hpp"

using namespace Nata;
using namespace glm;

int main(int argc, char** argv)
{
    NWorld* world = new NWorld();
    OurGameMode* gameMode = new OurGameMode();
    //world->SetGameMode((NGameMode*)gameMode);

    Window* win = new Window("OpenGL Studies", 700, 500);
    Input* input = win->GetInput();

    float deltaTime = 0.f;
    double lastFrame = 0.f;

    world->Begin();
    while (!win->Closed())
    {
        world->Tick();
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        win->Update();
    }
}