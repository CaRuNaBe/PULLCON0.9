/*****************************************************************//**
 * \file   StartLogo.h
 * \brief  
 * 
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class StartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	StartLogo();
	~StartLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KGAMESTARTLOGO;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game );
	bool	Draw( ApplicationBase& game );

private:
	int		_cg;		// �摜

};