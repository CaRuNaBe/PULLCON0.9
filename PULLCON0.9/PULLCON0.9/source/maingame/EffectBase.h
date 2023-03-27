#pragma once
#include "ActorBase3D.h"
#include "appframe.h"
#include "../mode/ModeMainGame.h"
class EffectBase:public ActorBase3D
{
	using  base = ActorBase3D;
public:
	EffectBase( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectBase();
	virtual Type GetType()
	{
		return Type::kEffect;
	}

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	int _grHandle;  // 現在のグラフィックハンドル
	std::vector<int>_grAllHandles;// 全てのグラフィックハンドル
	int _animeNo;// アニメ番号
	int _animeMax;// アニメ最大数
	int _animeCnt;// アニメカウント
};

