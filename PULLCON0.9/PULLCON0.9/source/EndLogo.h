#pragma once
#include "ActorBase2d.h"
class EndLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	EndLogo();
	~EndLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KENDLOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// �摜
};

