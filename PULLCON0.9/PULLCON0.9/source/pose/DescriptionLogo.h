#pragma once
#include "appframe.h"
class DescriptionLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	DescriptionLogo( ApplicationBase& game,ModeBase& mode );
	~DescriptionLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KDESCRIPTIONLOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();
private:
	int FontHandle;
};

