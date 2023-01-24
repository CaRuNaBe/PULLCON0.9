#pragma once
#include "appframe.h"
class ReturnTitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	ReturnTitleLogo();
	~ReturnTitleLogo();
	virtual Type	GetType()//©•ª‚ª‰½Ò‚©
	{
		return Type::KRETURNTITLELOGO;
	}

	void	Init();//‰Šú‰»
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

