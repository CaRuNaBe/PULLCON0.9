/*****************************************************************//**
 * \file   ModeGameResult.h
 * \brief  リザルト画面クラス
 * 
 * \author 阿部健太郎
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
	virtual bool Update();/*計算処理*/
	virtual bool Draw();/*描画*/
private:
};

