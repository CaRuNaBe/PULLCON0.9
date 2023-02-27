#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class AreaEnemySpawn:public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaEnemySpawn( ApplicationBase& game,ModeMainGame& mode,  int spawnfream,int typeenemy );
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

