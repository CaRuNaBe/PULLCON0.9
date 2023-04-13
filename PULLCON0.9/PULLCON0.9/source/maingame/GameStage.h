#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class GameStage :public ActorMainGame
{
public:
	GameStage(ApplicationBase& game, int layer, ModeMainGame& mode, int stageid);
	virtual ~GameStage();

	virtual Type GetType()
	{
		return Type::kGameStage;
	}
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual int& GetHandle()
	{
		return _handle;
	}

protected:
	int    _handle;
};

