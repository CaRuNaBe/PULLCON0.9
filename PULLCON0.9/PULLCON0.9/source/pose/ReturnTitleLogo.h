#pragma once
#include "appframe.h"
class ReturnTitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	ReturnTitleLogo( ApplicationBase& game,ModeBase& mode );
	~ReturnTitleLogo();
	virtual Type	GetType()//©•ª‚ª‰½Ò‚©
	{
		return Type::KRETURNTITLELOGO;
	}

	void	Init();//‰Šú‰»
	bool	Update();
	bool	Draw();
private:
	int FontHandle;
};

