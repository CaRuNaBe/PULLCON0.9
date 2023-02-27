#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class StartGuid:public ActorBase2d
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
	StartGuid( ApplicationBase& game,ModeTitle& mode );
	~StartGuid();
	virtual Type	GetType()//���������҂�
	{
		return Type::KGAMESTARTGUID;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// �摜
};

