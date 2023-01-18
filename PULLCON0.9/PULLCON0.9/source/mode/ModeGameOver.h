/*****************************************************************//**
 * \file   ModeGameOver.h
 * \brief  ゲームオーバー画面
 * 
 * \author 阿部健太郎
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
	virtual bool Update();/*計算処理*/
	virtual bool Draw();/*描画*/
private:
};

