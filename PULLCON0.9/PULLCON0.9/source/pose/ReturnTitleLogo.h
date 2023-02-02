#pragma once
#include "appframe.h"
class ReturnTitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	ReturnTitleLogo( ApplicationBase& game,ModeBase& mode );
	~ReturnTitleLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KRETURNTITLELOGO;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();
private:
	int FontHandle;
};

