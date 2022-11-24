#pragma once
#include "nata.h"
#include "exercises/exercises.hpp"

using namespace Nata;
using namespace glm;

int main(int argc, char** argv)
{
    Window* win = new Window("OpenGL Studies", 700, 500);
    Input* input = win->GetInput();

    Shader shader("src\\shaders\\lit.vert", "src\\shaders\\lit.frag");
    Shader lightShader("src\\shaders\\unlit.vert", "src\\shaders\\unlit.frag");

    Texture texture("container2.png", "res", TEXTURE_DIFFUSE);
    Model ourModel("res\\models\\teapot.obj");
    ourModel.AddTexture(texture);

    glEnable(GL_DEPTH_TEST);

    // view and projection matrices
    mat4 view = mat4(1.0f);
    mat4 projection;
    projection = perspective(radians(45.0f), 700.f / 500.f, 0.1f, 100.0f);

    // 1. initial camera settings
    const float camSpeed = 2.f;
    const float camSens = 1.f;
    float pitch = 0.f;
    float yaw = -90.f;
    vec3 camPos = vec3(0.f, 0.f, 3.f);

    vec2 lastMousePos = vec2(0.f, 0.f);
    float deltaTime = 0.f;
    double lastFrame = 0.f;

    const float rotationSpeed = .5f;

    while (!win->Closed())
    {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        vec2 mousePos = input->GetMousePos();
        vec2 mouseDelta = vec2(mousePos.x - lastMousePos.x, mousePos.y - lastMousePos.y);
        lastMousePos = mousePos;

        win->Clear();
        float time = (float)glfwGetTime();

        vec3 pointLightPositions[] =
        {
            vec3(1.f, 1.f, 0.f),
            vec3(-1.f, 1.f, 0.f)
        };

        float lightIntensity = (sin(time) + 1) * 2.f;
        vec3 pointLightColors[] =
        {
            vec3(1.f, 0.f, 0.f) * lightIntensity,
            vec3(0.f, 0.f, 5.f)
        };

        // camera
        vec3 camForward;
        camForward.x = cos(yaw) * cos(pitch);
        camForward.y = sin(pitch);
        camForward.z = sin(yaw) * cos(pitch);
        camForward = normalize(camForward);
        vec3 camRight = glm::normalize(glm::cross(vec3(0.f, 1.f, 0.f), camForward));
        vec3 camUp = glm::cross(camForward, camRight);
        view = lookAt(camPos, camPos + camForward, camUp);

        if (input->GetKeyDown(GLFW_KEY_W))
        {
            camPos += camSpeed * camForward * deltaTime;
        }
        if (input->GetKeyDown(GLFW_KEY_S))
        {
            camPos -= camSpeed * camForward * deltaTime;
        }
        if (input->GetKeyDown(GLFW_KEY_A))
        {
            camPos += camSpeed * camRight * deltaTime;
        }
        if (input->GetKeyDown(GLFW_KEY_D))
        {
            camPos -= camSpeed * camRight * deltaTime;
        }

        // camera transformations
        shader.Enable();
        shader.SetUniform3f("color", vec3(1.f, 1.f, 1.f));
        shader.SetUniformMat4("view", view);
        shader.SetUniformMat4("projection", projection);

        // shader uniforms
        shader.SetUniform1f("shininess", 32.f);
        shader.SetUniform3f("dirLight.direction", vec3(0.f, -1.f, 0.f));
        shader.SetUniform3f("dirLight.ambient", vec3(0.f, 0.f, 0.f));
        shader.SetUniform3f("dirLight.diffuse", vec3(1.f, 1.f, 1.f));
        shader.SetUniform3f("dirLight.specular", vec3(1.f, 1.f, 1.f));
        shader.SetUniform3f("dirLight.color", vec3(1.f, 1.f, 1.f));
        shader.Disable();

        for (int i = 0; i < 2; i++)
        {
            shader.Enable();
            // point light
            shader.SetUniform3f(("pointLights[" + std::to_string(i) + "].ambient").c_str(), .2f, .2f, .2f);
            shader.SetUniform3f(("pointLights[" + std::to_string(i) + "].diffuse").c_str(), .5f, .5f, .5f);
            shader.SetUniform3f(("pointLights[" + std::to_string(i) + "].specular").c_str(), 1.f, 1.f, 1.f);

            shader.SetUniform3f(("pointLights[" + std::to_string(i) + "].color").c_str(), pointLightColors[i]);

            // attenuation
            shader.SetUniform3f(("pointLights[" + std::to_string(i) + "].position").c_str(), pointLightPositions[i]);
            shader.SetUniform1f(("pointLights[" + std::to_string(i) + "].constant").c_str(), 1.f);
            shader.SetUniform1f(("pointLights[" + std::to_string(i) + "].linear").c_str(), 0.027f);
            shader.SetUniform1f(("pointLights[" + std::to_string(i) + "].quadratic").c_str(), 0.028f);
            shader.Disable();
        }

        shader.Enable();
        vec3 position = vec3(0.f, 0.f, 0.f);
        mat4 model = mat4(1.0f);
        model = translate(model, position);
        model = rotate(model, time * rotationSpeed, vec3(0.f, 1.f, 0.f));
        shader.SetUniformMat4("model", model);
        shader.Disable();

        //ourMesh.DrawArrays(shader);
        ourModel.Draw(shader);

        win->Update();
    }
}