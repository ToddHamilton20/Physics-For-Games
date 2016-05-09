#include "Engine.h"
#include "Window.h"
#include "BaseState.h"

void Engine::Run(BaseState* a_state)
{
	glfwInit();

	PushState(a_state);
	double prevTime = glfwGetTime();
	double currTime = glfwGetTime();

	while (stateStack.size() > 0)
	{
		currTime = glfwGetTime();
		BaseState* state = stateStack[stateStack.size() - 1];
		state->Update(currTime - prevTime);
		glfwPollEvents();

		if (quitFlag || stateStack.size() <= 0)
			break;
		if (popFlag)
		{
			popFlag = false;
			continue;
		}

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		state->Draw();
		Window::GetInstance().SwapBuffers();
		prevTime = currTime;
	}

	while (stateStack.size() > 0)
		PopState();
}

void Engine::PushState(BaseState* a_state)
{
	stateStack.push_back(a_state);
	a_state->Startup();
}

void Engine::PopState()
{
	BaseState* state = stateStack[stateStack.size() - 1];
	stateStack.pop_back();
	state->Shutdown();
	delete state;
	popFlag = true;
}

void Engine::Quit()
{
	quitFlag = true;
}