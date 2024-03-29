#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyGunShip :public ActorMainGame
{
public:
	EnemyGunShip(ApplicationBase& game, int layer, ModeMainGame& mode, float _radius);
	virtual ~EnemyGunShip();
	virtual Type GetType()
	{
		return Type::kEnemyGunShip;
	}
	// ガンシップの状態
	enum class State
	{
		NUM, //初期状態
		WAIT,//待機状態
		PLAY,//迎撃体制
	};
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();

protected:
	State   _stateClearObject;

	Vector4 _vObjective;  // 円軌道中心座標

	int    _handle;
	float radius;
};

