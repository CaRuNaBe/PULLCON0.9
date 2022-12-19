#pragma once
#include "ActorBase2d.h"
class EndLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	EndLogo();
	~EndLogo();
	virtual Type	GetType()//©•ª‚ª‰½Ò‚©
	{
		return Type::KENDLOGO;
	}

	void	Init();//‰Šú‰»
	bool	Update( ApplicationBase& game );
	bool	Draw( ApplicationBase& game );

private:
	int		_cg;		// ‰æ‘œ
};

