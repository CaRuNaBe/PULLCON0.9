#pragma once
#include "ActorBase2d.h"
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
	bool	Update( ApplicationBase& game );
	bool	Draw( ApplicationBase& game );

private:
	int		_cg;		// 画像
};

