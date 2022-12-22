/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  �^�C�g���p�v���C���[�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class TitlePlayer:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	/**
	 * �v���C���[�̏��.
	 */
	enum class State
	{
		IDLING,//�ҋ@
		MOVING,//�ړ�
		PULLING//������
	};
	TitlePlayer();
	~TitlePlayer();
	virtual Type	GetType()
	{
		return Type::KPLAYER;
	}

	void	Init();//������
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		cg_player;		// �v���C���[�摜
	int  cg_ui;//ui�摜
	bool isRight;//�E�����`��̎�true
	bool isUidraw;
};

