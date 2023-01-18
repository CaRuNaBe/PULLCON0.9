#pragma once
#include "appframe.h"

class EffectTrail : public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EffectTrail();
	virtual ~EffectTrail();
	virtual Type GetType() { return Type::kEffect; }

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

protected:

	int _grHandle;  // 現在のグラフィックハンドル
	std::vector<int>_grAllHandles;// 全てのグラフィックハンドル
	int _animeNo;// アニメ番号
	int _animeMax;// アニメ最大数
	int _animeCnt;// アニメカウント
};

