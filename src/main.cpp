#pragma once
#include "nata.h"
#include "core/ecs/ecs.h"

#include "core/ecs/EOurObject.hpp"
#include "core/ecs/EOurGameMode.hpp"

using namespace Nata;
using namespace glm;

namespace Nata
{
    class NTime
    {
    public:
        static float Time;
        static float DeltaTime;
    };

    float NTime::Time = 0.f;
    float NTime::DeltaTime = 0.f;

    static NWindow* Window = nullptr;
}


int main(int argc, char** argv)
{
    NWorld* world = new NWorld();
    NOurGameMode* gameMode = new NOurGameMode();
    world->SetGameMode(gameMode);
    EOurObject* entity = world->Instantiate<EOurObject>();

    NWindow* win = new NWindow("OpenGL Studies", 700, 500);
    Window = win;
    NRenderer* renderer = win->GetRenderer();
    Input* input = win->GetInput();

    NShader* ourShader = new NShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");
    NTexture* ourTexture = new NTexture("container2.png", "res", TEXTURE_DIFFUSE);
    NModel* ourModel = new NModel("res\\models\\teapot.obj");
    NModel* ourOtherModel = new NModel("res\\models\\teapot.obj");

    //entity->MeshRenderer->Shader = shader;
    //entity->MeshRenderer->Texture = texture;
    //entity->MeshRenderer->Model = model;

    glEnable(GL_DEPTH_TEST);

    // view and projection matrices
    mat4 view = mat4(1.f);
    mat4 projection;
    projection = perspective(radians(45.0f), 700.f / 500.f, 0.1f, 100.0f);

    // 1. initial camera settings
    const float camSpeed = 2.f;
    const float camSens = 1.f;
    float pitchDeg = 0.f;
    float yawDeg = -90.f;
    vec3 camPos = vec3(0.f, 0.f, 8.f);
    vec2 lastMousePos = vec2(0.f, 0.f);
    const float rotationSpeed = .5f;

    float deltaTime = 0.f;
    double lastFrame = 0.f;

    ourModel->Shader = *ourShader;
    ourOtherModel->Shader = *ourShader;

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

        // camera
        vec3 camForward;
        float yaw = radians(yawDeg);
        float pitch = radians(pitchDeg);

        camForward.x = cos(yaw) * cos(pitch);
        camForward.y = sin(pitch);
        camForward.z = sin(yaw) * cos(pitch);
        camForward = normalize(camForward);
        vec3 camRight = glm::normalize(glm::cross(vec3(0.f, 1.f, 0.f), camForward));
        vec3 camUp = glm::cross(camForward, camRight);
        view = lookAt(camPos, camPos + camForward, camUp);

        // camera transformations
        ourShader->Enable();
        ourShader->SetUniform3f("color", vec3(1.f, 1.f, 1.f));
        ourShader->SetUniformMat4("view", view);
        ourShader->SetUniformMat4("projection", projection);

        ourModel->Position = vec3(0.f);
        renderer->Submit(ourModel);

        ourOtherModel->Position = vec3(0.f, 2.f, 0.f);
        renderer->Submit(ourOtherModel);

        win->Update();
    }
}