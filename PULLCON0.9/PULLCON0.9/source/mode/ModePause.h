/*****************************************************************//**
 * \file   ModePause.h
 * \brief  �|�[�Y��ʃN���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ModePause:public ModeBase
{
	using base = ModeBase;
public:
	ModePause( ApplicationBase& game,int layer );
	virtual ~ModePause();
	virtual bool Initialize();
	virtual bool Update();/*�v�Z*/
	virtual bool Draw();/*�`��*/
private:
};

