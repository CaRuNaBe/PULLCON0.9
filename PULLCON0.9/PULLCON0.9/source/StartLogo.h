/*****************************************************************//**
 * \file   StartLogo.h
 * \brief  
 * 
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class StartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	StartLogo();
	~StartLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KGAMESTARTLOGO;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// 画像

};