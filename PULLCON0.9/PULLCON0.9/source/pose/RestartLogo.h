#pragma once
#include "appframe.h"
class RestartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	RestartLogo();
	~RestartLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KRESTARTLOGO;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

