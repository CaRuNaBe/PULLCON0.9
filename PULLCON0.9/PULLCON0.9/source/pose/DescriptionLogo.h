#pragma once
#include "appframe.h"
class DescriptionLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	DescriptionLogo();
	~DescriptionLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KDESCRIPTIONLOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};

