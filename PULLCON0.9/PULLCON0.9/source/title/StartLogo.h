/*****************************************************************//**
 * \file   StartLogo.h
 * \brief  �Q�[���X�^�[�g���S�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class StartLogo:public ActorBase2d
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
	StartLogo( ApplicationBase& game,ModeTitle& mode );
	~StartLogo();
	virtual Type	GetType()//���������҂�
	{
		return Type::KGAMESTARTLOGO;
	}

	void	Init();//������
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// �摜

};