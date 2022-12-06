#pragma once
#include "nata.h"
#include "editor.h"
#include "core/window.h"

using namespace Nata;
using namespace glm;

void Execute()
{
    NWorld* world = new NWorld();
    NEngine::World = world;
    NOurGameMode* gameMode = new NOurGameMode();
    world->SetGameMode(gameMode);

    ECamera* camera = Instantiate<ECamera>(world);
    NEngine::Camera = camera->Camera;

    EOurObject* object1 = Instantiate<EOurObject>(world);
    EOurObject* object2 = Instantiate<EOurObject>(world, vec3(2.f, 0.f, 0.f));

    object2->Transform->SetParent(object1->Transform);
}

int main(int argc, char** argv)
{
    NWindow* window = new NWindow("Game", NEngine::WindowSizeX, NEngine::WindowSizeY);
    
    NRenderer* renderer = window->GetRenderer();
    NEngine::Window = window;
    NEngine::Input = window->GetInput();

    glEnable(GL_DEPTH_TEST);

    Execute();
    if (NEngine::World == nullptr)
    {
        std::cout << "ERROR::WORLD : INVALID WORLD" << std::endl;
        return 0;
    }
    if (NEngine::Camera == nullptr)
    {
        std::cout << "WARNING::CAMERA : INVALID CAMERA" << std::endl;
    }

    float deltaTime = 0.f;
    double lastFrame = 0.f;

    NWorld* world = NEngine::World;
    world->Begin();
    while (!window->Closed())
    {   
        window->Clear();
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        NTime::Time = (float)glfwGetTime();
        NTime::DeltaTime = deltaTime;

        world->Tick(deltaTime);
        window->Update();
    }
}