#pragma once
#include "appframe.h"

class EnemySpawnEria:public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemySpawnEria( int spawnfream,int typeenemy );
	virtual ~EnemySpawnEria();
	virtual Type GetType()
	{
		return Type::kEnemySpawnEria;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int spawn_fream;
	int type_enemy;
};

