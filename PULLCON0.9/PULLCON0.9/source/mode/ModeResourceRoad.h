/*****************************************************************//**
 * \file   ModeResourceRoad.h
 * \brief  ���\�[�X���[�h���\����ʃN���X
 *
 * \author ���������Y
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
class Game;
class ModeResourceRoad :public ModeBase
{
public:
	ModeResourceRoad ( Game& game );
	virtual ~ModeResourceRoad ();

	virtual void Update ();  // �X�V
	virtual void Render ();	// �`��
private:
};

