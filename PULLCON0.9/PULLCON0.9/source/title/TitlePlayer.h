/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  �^�C�g���p�v���C���[�N���X��`
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "array"
class TitlePlayer:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	/**
	 * �v���C���[�̏��.
	 */
	enum class State
	{
		MOVE,//����
		WAIT//�҂�
	};
	/** �R���X�g���N�^ */
	TitlePlayer( ApplicationBase& game,ModeBase& mode );
	/** �f�X�g���N�^ */
	~TitlePlayer();

	virtual Type	GetType()//���������҂�
	{
		return Type::KPLAYER;
	}

	void	Init();//������
	bool	Update();//�X�V
	bool	Draw();//�`��

private:
	int		cg_player;		// �v���C���[�摜
	std::array<int,4> cg_ui;//ui�摜
	bool isRight;//�E�����`�悵�Ă鎞true
	bool isUidraw;//�{�^���\������true�̎��\��
	int waitTime;
	State PlayerState;
};

