/*****************************************************************//**
 * \file   ModeGameOver.h
 * \brief  �Q�[���I�[�o�[���
 * 
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ModeGameOver: public ModeBase
{
	typedef ModeBase base;
public:
	ModeGameOver(ApplicationBase& game,int layer);
	virtual ~ModeGameOver();
	virtual bool Initialize();
	virtual bool Update();/*�v�Z����*/
	virtual bool Draw();/*�`��*/
private:
};

