#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "Engine.h"
#include "Window.h"
#include "MenuState.h"
#include <time.h>

int main()
{
	Window::GetInstance().InitialiseWindow("Todd Hamilton - Evolution Application", 1280, 720);

	srand((unsigned int)time(0));
	Engine engine;
	engine.Run(new MenuState(&engine));

	return 0;
}