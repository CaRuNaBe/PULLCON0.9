#pragma once
#include "appframe.h"
class GameStage :public ActorBase3D {
	using base = ActorBase3D;
public:
	GameStage(ApplicationBase& game, ModeBase& mode, int stageid);
	virtual ~GameStage();

	virtual Type GetType() { return Type::kGameStage; }
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
};

