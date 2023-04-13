#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class AreaSupply :public ActorMainGame
{
public:
	AreaSupply(ApplicationBase& game, int layer, ModeMainGame& mode, float _radius);
	virtual ~AreaSupply();
	virtual Type GetType()
	{
		return Type::kAreaSupply;
	}
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
};

