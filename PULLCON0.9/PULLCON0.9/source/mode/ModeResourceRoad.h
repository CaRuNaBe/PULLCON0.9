/*****************************************************************//**
 * \file   ModeResourceRoad.h
 * \brief  リソースロード中表示画面クラス
 *
 * \author 阿部健太郎
 * \date   September 2022
 *********************************************************************/
#pragma once
#include "ModeBase.h"
class Game;
class ModeResourceRoad :public ModeBase
{
public:
	ModeResourceRoad ( Game& game );
	virtual ~ModeResourceRoad ();

	virtual void Update ();  // 更新
	virtual void Render ();	// 描画
private:
};

