/*****************************************************************//**
 * \file   ModeGameResult.h
 * \brief  ���U���g��ʃN���X
 * 
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ModeGameResult:public ModeBase
{
	typedef ModeBase base;
public:
	ModeGameResult(ApplicationBase& game,int layer);
	virtual ~ModeGameResult();
	virtual bool Initialize();
	virtual bool Update();/*�v�Z����*/
	virtual bool Draw();/*�`��*/
private:
};

