#pragma once
#include "appframe.h"


class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num );
	virtual ~EnemyAAA();
	virtual Type GetType()
	{
		return Type::kEnemyAAA;
	}
// 対空砲の状態
	enum class State
	{
		PLAY,//プレイアブル状態
		EVENT,//イベント状態
		WEAPON//兵器化
	};

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage( );
	void AddBullet(  );

protected:
	State   _stateAAA;

	int    _handle_body;
	int    _handle_turret;

};
