#pragma once
#include "appframe.h"
class ReturnTitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	ReturnTitleLogo();
	~ReturnTitleLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KRETURNTITLELOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

