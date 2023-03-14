/*****************************************************************//**
 * \file   TitlePlayer.h
 * \brief  タイトル用プレイヤークラス定義
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
#include "array"
class TitlePlayer:public ActorTitle
{
public:
	/**
	 * プレイヤーの状態.
	 */
	enum class State
	{
		MOVE,//動く
		WAIT//待つ
	};
	/** コンストラクタ */
	TitlePlayer( ApplicationBase& game,int layer,ModeTitle& mode );
	/** デストラクタ */
	~TitlePlayer();

	virtual Type	GetType()//自分が何者か
	{
		return Type::KPLAYER;
	}

	void	Initialize();//初期化
	bool	Update();//更新
	bool	Draw();//描画

private:
	int cg_player;		// プレイヤー画像
	std::array<int,4> cg_ui;//ui画像
	bool isRight;//右向き描画してる時true
	bool isUidraw;//ボタン表示判定trueの時表示
	int waitTime;
	State PlayerState;
};

