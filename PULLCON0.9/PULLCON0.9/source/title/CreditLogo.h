/*****************************************************************//**
 * \file   CreditLogo.h
 * \brief  クレジットロゴオブジェクトクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class CreditLogo:
	public ActorTitle
{
		/**
	 * オブジェクトの状態.
	 */
	enum class State
	{
		IDLING,//待機
		PULLED//引っ張られている
	};
public:
	CreditLogo( ApplicationBase& game,int layer,ModeTitle& mode );
	~CreditLogo();
	virtual Type GetType()//自分が何者か
	{
		return Type::KCREDITLOGO;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

