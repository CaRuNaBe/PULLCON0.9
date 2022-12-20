/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  タイトル用プレイヤークラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ActorBase2d.h"
#include "ActorBase.h"
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
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// 画像
	bool isRight;//右向き描画の時true
};

