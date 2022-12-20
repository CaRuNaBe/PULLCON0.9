#pragma once

class ApplicationBase;

#include	"../Object/ObjectServer.h"


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
protected:
	ApplicationBase& _game;
	bool	_dead;
	bool _isModeSkip;
	bool _isDrawSkip;
	int _layer;
};
