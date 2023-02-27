#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class GameStage:public ActorBase3D
{
	using base = ActorBase3D;
public:
	GameStage( ApplicationBase& game,ModeMainGame& mode,int stageid );
	virtual ~GameStage();

	virtual Type GetType()
	{
		return Type::kGameStage;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
};

