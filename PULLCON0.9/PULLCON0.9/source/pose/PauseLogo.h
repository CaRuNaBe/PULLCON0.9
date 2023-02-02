/*****************************************************************//**
 * \file   PauseLogo.h
 * \brief  ポーズ画面のui文字
 *
 * \author 阿部健太郎
 * \date   January 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
class PauseLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	PauseLogo( ApplicationBase& game,ModeBase& mode );
	~PauseLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KPAUSELOGO;//自分はポーズ画面の表示ロゴ
	}

	void	Init();//初期化
	bool	Update( );
	bool	Draw( );
private:
	int FontHandle;
};

