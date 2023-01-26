#pragma once
#include "appframe.h"
class GameStage:public ActorBase3D
{
	using base = ActorBase3D;
public:
	GameStage( int stageid );
	virtual ~GameStage();
	virtual Type GetType()
	{
		return Type::kGameStage;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int    _handle;
};

