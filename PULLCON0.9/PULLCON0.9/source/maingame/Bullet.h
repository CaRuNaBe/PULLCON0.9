#pragma once
#include "appframe.h"

class Bullet : public ActorBase3D{
	typedef ActorBase3D base;
public:
	Bullet( ApplicationBase& game,ModeBase& mode);
	virtual ~Bullet();
	virtual Type GetType() { return Type::kBullet; }

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();

protected:

	int    _handle;
	
	int _grHandle;  // 現在のグラフィックハンドル
	std::vector<int>_grAllHandles;// 全てのグラフィックハンドル
	int _animeNo;// アニメ番号
	int _animeMax;// アニメ最大数
};

