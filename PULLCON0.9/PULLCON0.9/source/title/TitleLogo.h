/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  �^�C�g�����S�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class TitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	TitleLogo( ApplicationBase& game,ModeTitle& mode );
	~TitleLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KTITLELOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// �摜
};

