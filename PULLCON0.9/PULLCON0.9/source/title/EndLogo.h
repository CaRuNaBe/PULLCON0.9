#pragma once
#include "appframe.h"
class EndLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
		/**
	 * �I�u�W�F�N�g�̏��.
	 */
	enum class State
	{
		IDLING,//�ҋ@
		PULLED//���������Ă���
	};
public:
	EndLogo( ApplicationBase& game,ModeBase& mode );
	~EndLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KENDLOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// �摜
};

