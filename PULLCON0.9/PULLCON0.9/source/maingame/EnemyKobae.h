#pragma once
#include "appframe.h"
class EnemyKobae :
    public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyKobae(ApplicationBase& game, ModeBase& mode);
	virtual ~EnemyKobae();
	virtual Type GetType() {
		return Type::kEnemySkyhunter;
	}
	// コバエの状態
	enum class State {
		WAIT,//待機状態
		PLAY,//迎撃体制
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // 速度ベクトル
	void AddBullet();

protected:
	State   _stateEnemyKobae;

	int    _handle;
};

