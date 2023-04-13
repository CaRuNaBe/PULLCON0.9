#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class AreaNoEntry :public ActorMainGame
{
public:
	AreaNoEntry(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~AreaNoEntry();
	virtual Type GetType()
	{
		return Type::kStageObject;
	}
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

protected:

};

