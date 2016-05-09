// Author:					Todd Hamilton
// Description of File:		BaseApplication class. 

#pragma once

class Engine;

class BaseState
{
public:

	BaseState(Engine* a_engine) : engine(a_engine) {}
	virtual ~BaseState() {}

	virtual bool Startup() = 0;
	virtual void Shutdown() = 0;

	virtual bool Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	Engine* engine;
};