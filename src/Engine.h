// Author:					Todd Hamilton
// Last Change:				03/05/16
// Description of File:		Engine class

#pragma once

#include <vector>

class BaseState;

class Engine
{
public:
	Engine() : quitFlag(false) {}
	void Run(BaseState* a_state);
	void PushState(BaseState* a_state);
	void PopState();
	void Quit();

private:
	std::vector<BaseState*> stateStack;
	bool quitFlag, popFlag;
};