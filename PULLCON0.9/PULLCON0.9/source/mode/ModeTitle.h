#pragma once
#include<memory>
#include "appframe.h"
class ActorBase2d;
class ModeTitle:public GameBase
{
	using base = GameBase;
public:
	ModeTitle( ApplicationBase& game,int layer );
	virtual ~ModeTitle();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
	ObjectServer<ActorBase2d>& Get2DobjectServer()
	{
		return object_out_game;
	}
private:
	ObjectServer<ActorBase2d> object_out_game;
};