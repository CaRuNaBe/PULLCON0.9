#pragma once
#include "appframe.h"
class RestartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	RestartLogo( ApplicationBase& game,ModeBase& mode );
	~RestartLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KRESTARTLOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();
private:
	int FontHandle;
};

