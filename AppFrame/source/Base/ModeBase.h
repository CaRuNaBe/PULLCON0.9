#pragma once
#include"../Object/ObjectServer.h"
#include "../Base/GameBase.h"
class ApplicationBase;
class ActorBase2d;
class ActorBase3D;
class ActorBaseSpeak;
class ModeBase:public GameBase
{
public:
	ModeBase( ApplicationBase& game,int layer );
	virtual ~ModeBase();
	virtual bool Initialize();
	virtual bool Update();  // çXêV
	virtual bool Draw();// ï`âÊ
	virtual bool DebugDraw();
	
	ObjectServer<ActorBase2d>& Get2DobjectServer()
	{
		return object_out_game;
	}

	ObjectServer<ActorBase3D>& GetObjectServer3D()
	{
		return object_main_game;
	}
protected:
	ObjectServer<ActorBase2d> object_out_game;
	ObjectServer<ActorBase3D> object_main_game;

};
