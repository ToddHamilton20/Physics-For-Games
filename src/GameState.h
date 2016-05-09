#pragma once

#include "BaseState.h"

class GameState : public BaseState
{
public:
	GameState(Engine* a_engine) : BaseState(a_engine) {}

	bool Startup();
	bool Update(float a_deltaTime);
	void Draw();
	void Shutdown();

private:
};