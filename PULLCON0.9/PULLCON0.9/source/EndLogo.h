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
	bool	Update( ApplicationBase& game );
	bool	Draw( ApplicationBase& game );

private:
	int		_cg;		// �摜
};

