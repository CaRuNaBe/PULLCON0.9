/*****************************************************************//**
 * \file   CreditLogo.h
 * \brief  �N���W�b�g���S�I�u�W�F�N�g�N���X
 * 
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class CreditLogo:
    public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	CreditLogo();
	~CreditLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KCREDITLOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// �摜
};

