#pragma once
#include "appframe.h"
class ReturnTitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	ReturnTitleLogo( ApplicationBase& game,ModeBase& mode );
	~ReturnTitleLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KRETURNTITLELOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();
private:
	int FontHandle;
};

