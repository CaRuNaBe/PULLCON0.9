#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class AreaEnemySpawn :public ActorBase3D {
	using base = ActorBase3D;
public:
	AreaEnemySpawn(ApplicationBase& game, ModeMainGame& mode, int spawnfream, int typeenemy);
	virtual ~AreaEnemySpawn();
	virtual Type GetType() { return Type::kAreaEnemySpawn; }
	// 空中飛行基地の状態
	enum class State {
		NUM, //初期状態
		WAIT,//待機状態
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void  AddEnemyColumn();
	void  AddEnemyKobae();
protected:
	State  _stateEnemySpawn;

	int  _iSpawnFream;  // 敵をスポーンさせる間隔
	int  _iEnemyType;   // どの敵スポーンさせるかの設定
	bool _isAddKobae;   // コバエをスポーンさせるか

	int _handle;
};

