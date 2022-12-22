/*****************************************************************//**
 * \file   CreditLogo.h
 * \brief  クレジットロゴオブジェクトクラス
 * 
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class CreditLogo:
    public ActorBase2d
{
	using Actor2d = ActorBase2d;
		/**
	 * オブジェクトの状態.
	 */
	enum class State
	{
		IDLING,//待機
		PULLED//引っ張られている
	};
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

