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
	PauseLogo();
	~PauseLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KPAUSELOGO;//�����̓|�[�Y��ʂ̕\�����S
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );
private:
	int FontHandle;
};
