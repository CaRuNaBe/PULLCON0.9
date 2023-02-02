#include "EnemySpawnEria.h"
EnemySpawnEria::EnemySpawnEria( ApplicationBase& game,ModeBase& mode,int spawnfream,int typeenemy )
	:base( game,mode )
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
bool EnemySpawnEria::Update( )
{
	return true;
};
bool EnemySpawnEria::Draw( )
{
	return true;
};
