/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  タイトル用プレイヤークラス
 * 
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
class TitlePlayer:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	/**
	 * プレイヤーの状態.
	 */
	enum class State
	{
		IDLING,//待機
		MOVING,//移動
		PULLING//引張中
	};
	TitlePlayer();
	~TitlePlayer();
	virtual Type	GetType()
	{
		return Type::KPLAYER;
	}

	void	Init();//初期化
	bool	Update(ApplicationBase& game);
	bool	Draw(ApplicationBase& game);

private:
	int		_cg;		// 画像

};

