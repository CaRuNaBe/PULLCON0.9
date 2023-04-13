#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyColumn :public ActorMainGame
{
public:
	EnemyColumn(ApplicationBase& game, int layer, ModeMainGame& mode, Vector4 pos);
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
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // 速度ベクトル
	void AddPieces(Vector4 pos);

protected:
	State   _stateEnemyColumn;

	int    _handleStage;
};

