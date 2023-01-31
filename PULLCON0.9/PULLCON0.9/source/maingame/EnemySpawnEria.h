#pragma once
#include "appframe.h"

class EnemySpawnEria:public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemySpawnEria( ApplicationBase& game,ModeBase& mode,  int spawnfream,int typeenemy );
	virtual ~EnemySpawnEria();
	virtual Type GetType()
	{
		return Type::kEnemySpawnEria;
	}
	virtual void Init();
	virtual bool Update( );
	virtual bool Draw(  );

protected:
	int spawn_fream;
	int type_enemy;
};

