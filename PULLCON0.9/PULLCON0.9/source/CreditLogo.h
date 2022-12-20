/*****************************************************************//**
 * \file   CreditLogo.h
 * \brief  クレジットロゴオブジェクトクラス
 * 
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class CreditLogo:
    public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	CreditLogo();
	~CreditLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KCREDITLOGO;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// 画像
};

