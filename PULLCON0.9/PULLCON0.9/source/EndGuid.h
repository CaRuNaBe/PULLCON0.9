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
	EndGuid();
	~EndGuid();
	virtual Type	GetType()//���������҂�
	{
		return Type::KENDGUID;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// �摜
};

