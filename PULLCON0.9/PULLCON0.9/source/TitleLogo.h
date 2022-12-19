/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  �^�C�g�����S�N���X
 * 
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class TitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	TitleLogo();
	~TitleLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KTITLELOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game );
	bool	Draw( ApplicationBase& game );

private:
	int		_cg;		// �摜
};

