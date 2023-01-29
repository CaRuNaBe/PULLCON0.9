#include "EnemySpawnEria.h"
EnemySpawnEria::EnemySpawnEria( int spawnfream,int typeenemy )
{
	spawn_fream = spawnfream;
	/*
	switch ( typeenemy )
	{
		default:
			break;
	}
	*/
	Init();
};
EnemySpawnEria::~EnemySpawnEria()
{
};

void EnemySpawnEria::Init()
{
};
bool EnemySpawnEria::Update( ApplicationBase& game,ModeBase& mode )
{
	return true;
};
bool EnemySpawnEria::Draw( ApplicationBase& game,ModeBase& mode )
{
	return true;
};
