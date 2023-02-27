#pragma once
#include "appframe.h"
#include "EnemyColumn.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemySkyhunter :
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemySkyhunter(ApplicationBase& game,ModeMainGame& mode, EnemyColumn& skyhunter);
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

	virtual void Damage();
	void AddBullet();

protected:
	EnemyColumn& _column;

	State   _stateEnemySkyhunter;

	int    _handle;
};
