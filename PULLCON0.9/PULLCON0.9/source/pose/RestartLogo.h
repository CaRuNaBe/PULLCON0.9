#pragma once
#include "appframe.h"
class RestartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	RestartLogo();
	~RestartLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KRESTARTLOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

