/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  タイトル用プレイヤークラス定義
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "array"
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
	/** コンストラクタ */
	TitlePlayer();
	/** デストラクタ */
	~TitlePlayer();

	virtual Type	GetType()//自分が何者か
	{
		return Type::KPLAYER;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );//更新
	bool	Draw( ApplicationBase& game,ModeBase& mode );//描画

private:
	int		cg_player;		// プレイヤー画像
	std::array<int,4> cg_ui;//ui画像
	bool isRight;//右向き描画してる時true
	bool isUidraw;//ボタン表示判定trueの時表示
};

