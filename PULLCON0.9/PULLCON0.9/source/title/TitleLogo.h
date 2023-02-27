/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  タイトルロゴクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class TitleLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	TitleLogo( ApplicationBase& game,ModeTitle& mode );
	~TitleLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KTITLELOGO;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

