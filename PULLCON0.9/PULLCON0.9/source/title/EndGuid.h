#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
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
	EndGuid( ApplicationBase& game,ModeTitle& mode );
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

