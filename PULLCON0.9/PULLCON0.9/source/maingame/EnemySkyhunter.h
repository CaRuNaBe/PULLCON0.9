#pragma once
#include "appframe.h"
class EnemySkyhunter :
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemySkyhunter(ApplicationBase& game, ModeBase& mode);
	virtual ~EnemySkyhunter();
	virtual Type GetType()
	{
		return Type::kEnemySkyhunter;
	}
	// スカイハンターの状態
	enum class State
	{
		NUM, //初期状態
		WAIT,//待機状態
		PLAY,//迎撃体制
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage(ModeBase& mode);
	void AddBullet();

protected:
	State   _stateEnemySkyhunter;

	int    _handle;
};
