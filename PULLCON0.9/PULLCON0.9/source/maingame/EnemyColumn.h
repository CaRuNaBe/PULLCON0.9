#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemyColumn :
	public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyColumn(ApplicationBase& game,ModeMainGame& mode, vector4 pos);
	virtual ~EnemyColumn();
	virtual Type GetType() { return Type::kEnemySkyhunter; }
	// スカイハンター隊列の状態
	enum class State {
		WAIT,//待機状態
		PLAY,//隊列
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // 速度ベクトル
	void AddPieces(vector4 pos);

protected:
	State   _stateEnemyColumn;

};

