#pragma once
#include	"../Object/ObjectServer.h"

class ApplicationBase;
class ActorBase2d;
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
		return _objectServer;
	}
protected:
	ApplicationBase& _game;
	ObjectServer<ActorBase2d>_objectServer;

	bool	_dead;
	bool _isModeSkip;
	bool _isDrawSkip;
	int _layer;
};
