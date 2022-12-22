#pragma once
#include "nata.h"
#include "core/window.h"
#include "app.cpp"

int main(int argc, char** argv)
{
	NWindow* window = new NWindow("Game", NEngine::WindowSizeX, NEngine::WindowSizeY);

	NRenderer* renderer = window->GetRenderer();
	NEngine::Window = window;
	NEngine::Input = window->GetInput();
	Handles::Init();

	glEnable(GL_DEPTH_TEST);

	App::Begin();

	if (NEngine::World == nullptr)
	{
		std::cout << "ERROR::WORLD : INVALID WORLD" << std::endl;
		return 0;
	}

	float deltaTime = 0.f;
	double lastFrame = 0.f;

	NWorld* world = NEngine::World;
	world->Awake();
	world->Begin();

	if (NEngine::Camera == nullptr)
	{
		std::cout << "WARNING::CAMERA : INVALID CAMERA" << std::endl;
	}

	bool begin = true;
	while (!window->Closed())
	{
		window->Clear();
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		NTime::Time = (float)glfwGetTime();
		NTime::DeltaTime = deltaTime;

		NEngine::Input->Tick();
		App::Tick(deltaTime);
		world->Tick(deltaTime);
		window->Update();
	}
}