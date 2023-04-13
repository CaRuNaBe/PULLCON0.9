#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class SkySphere :public ActorMainGame
{
public:
	SkySphere(ApplicationBase& game, int layer, ModeMainGame& mode, int objectid);
	virtual ~SkySphere();
	virtual Type GetType()
	{
		return Type::kSkySphere;
	}
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
};

