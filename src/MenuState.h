#pragma once

#include "BaseState.h"

class MenuState : public BaseState
{
public:
	MenuState(Engine* a_engine) : BaseState(a_engine) {}

	bool Startup();
	bool Update(float a_deltaTime);
	void Draw();
	void Shutdown();

private:
};