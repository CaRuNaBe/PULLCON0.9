#pragma once
#include "Dxlib.h"
class ApplicationBase;
class ModeBase;
// ObjectBaseƒNƒ‰ƒX
class ObjectBase
{
public:
	ObjectBase( ApplicationBase& game,ModeBase& mode );
	virtual ~ObjectBase();

	virtual void	Init();
	virtual bool	Update();
	virtual bool	Draw();

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
		return isUpdateSkip;
	}
	void SetUpdateSkip( bool UpdateSkip )
	{
		isUpdateSkip = UpdateSkip;
	}
	bool GetDrawSkip()
	{
		return isDrawSkip;
	}
protected:
	bool	_dead;
	bool isUpdateSkip;
	bool isDrawSkip;
	ApplicationBase& _game;
	ModeBase& _mode;

};
