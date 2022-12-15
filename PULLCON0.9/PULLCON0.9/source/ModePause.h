/*****************************************************************//**
 * \file   ModePause.h
 * \brief  ポーズ画面クラス
 * 
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class ModePause:public ModeBase
{
	typedef ModeBase base;
public:
	ModePause(ApplicationBase& game,int layer);
	virtual ~ModePause();
	virtual bool Initialize();
	virtual bool Update();/*計算*/
	virtual bool Draw();/*描画*/
private:
};

