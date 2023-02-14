#pragma once
#include "appframe.h"

class AreaEnemySpawn:public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaEnemySpawn( ApplicationBase& game,ModeBase& mode,  int spawnfream,int typeenemy );
	virtual ~AreaEnemySpawn();
	virtual Type GetType()
	{
		return Type::kAreaEnemySpawn;
	}
	virtual void Init();
	virtual bool Update( );
	virtual bool Draw(  );

protected:
	int spawn_fream;
	int type_enemy;
};

