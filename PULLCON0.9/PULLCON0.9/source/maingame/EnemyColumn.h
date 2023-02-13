#pragma once
#include "appframe.h"
class EnemyColumn :
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemyColumn(ApplicationBase& game, ModeBase& mode);
	virtual ~EnemyColumn();
	virtual Type GetType()
	{
		return Type::kEnemySkyhunter;
	}
	// スカイハンター隊列の状態
	enum class State
	{
		WAIT,//待機状態
		PLAY,//隊列
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage(ModeBase& mode);
	void SetVelocity();   // 速度ベクトル
	void AddPieces();

protected:
	State   _stateEnemyColumn;

};

