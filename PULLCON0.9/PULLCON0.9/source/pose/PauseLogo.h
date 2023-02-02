/*****************************************************************//**
 * \file   PauseLogo.h
 * \brief  �|�[�Y��ʂ�ui����
 *
 * \author ���������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
class PauseLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	PauseLogo( ApplicationBase& game,ModeBase& mode );
	~PauseLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KPAUSELOGO;//�����̓|�[�Y��ʂ̕\�����S
	}

	void	Init();//������
	bool	Update( );
	bool	Draw( );
private:
	int FontHandle;
};

