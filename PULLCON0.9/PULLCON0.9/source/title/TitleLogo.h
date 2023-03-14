/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  タイトルロゴクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class TitleLogo:public ActorTitle
{
public:
	TitleLogo( ApplicationBase& game,int layer,ModeTitle& mode );
	~TitleLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KTITLELOGO;
	}

	void	Initialize();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

