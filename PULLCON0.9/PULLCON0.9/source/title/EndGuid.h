#pragma once
#include "appframe.h"
class EndGuid:public ActorBase2d
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
	EndGuid( ApplicationBase& game,ModeBase& mode );
	~EndGuid();
	virtual Type	GetType()//���������҂�
	{
		return Type::KENDGUID;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// �摜
};

