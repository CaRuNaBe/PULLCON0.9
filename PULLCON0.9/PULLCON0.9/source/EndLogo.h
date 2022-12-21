#pragma once
#include "appframe.h"
class EndLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	EndLogo();
	~EndLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KENDLOGO;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// 画像
};

