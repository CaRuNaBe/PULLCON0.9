#pragma once
#include	"../Object/ObjectServer.h"

class ApplicationBase;
class ActorBase2d;
class ActorBase3D;
class ActorBaseSpeak;

class ModeBase
{
public:
	ModeBase(ApplicationBase& game,int layer);
	virtual ~ModeBase();
	virtual	bool Initialize();
	virtual bool Update();  // çXêV
	virtual bool Draw();	// ï`âÊ

	virtual bool	IsDead()
	{
		return _dead;
	}

	virtual void	Dead()
	{
		_dead = true;
	}

	bool GetUpdateSkip()
	{
		return _isModeSkip;
	}
	bool GetDrawSkip()
	{
		return _isDrawSkip;
	}

	int GetLayer()
	{
		return _layer;
	}
	ObjectServer<ActorBase2d>& Get2DobjectServer()
	{
		return object_out_game;
	}

	ObjectServer<ActorBase3D>& GetObjectServer3D()
	{
		return object_main_game;
	}

	ObjectServer<ActorBaseSpeak>& GetObjectServerSpeak()
	{
		return speak_object;
	}
protected:
	ApplicationBase& _game;

	ObjectServer<ActorBase2d> object_out_game;
	ObjectServer<ActorBase3D> object_main_game;
	ObjectServer<ActorBaseSpeak> speak_object;

	bool	_dead;
	bool _isModeSkip;
	bool _isDrawSkip;
	int _layer;
};
