#pragma once
#include	"Math.h"
#include "Dxlib.h"
class ApplicationBase;

// ObjectBaseƒNƒ‰ƒX
class ObjectBase
{
public:
	ObjectBase();
	virtual ~ObjectBase();

	virtual void	Init();
	virtual void	Update(ApplicationBase& game);
	virtual void	Draw(ApplicationBase& game);

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
	bool GetDrawSkip()
	{
		return isDrawSkip;
	}
protected:
	bool	_dead;
	bool isUpdateSkip;
	bool isDrawSkip;

};
