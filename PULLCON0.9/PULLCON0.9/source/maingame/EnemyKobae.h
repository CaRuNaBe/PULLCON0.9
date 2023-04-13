#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyKobae :public ActorMainGame
{
public:
	EnemyKobae(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~EnemyKobae();
	virtual Type GetType()
	{
		return Type::kEnemySkyhunter;
	}
	// コバエの状態
	enum class State
	{
		WAIT,//待機状態
		PLAY,//迎撃体制
	};
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // 速度ベクトル
	void AddBullet();

protected:
	State   _stateEnemyKobae;

	int    _handle;
	int    _handleStage;
};

