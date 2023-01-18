#pragma once
#include "appframe.h"
class DescriptionLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	DescriptionLogo();
	~DescriptionLogo();
	virtual Type	GetType()//©•ª‚ª‰½Ò‚©
	{
		return Type::KDESCRIPTIONLOGO;
	}

	void	Init();//‰Šú‰»
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

