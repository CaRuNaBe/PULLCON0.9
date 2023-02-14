#include "AreaEnemySpawn.h"
AreaEnemySpawn::AreaEnemySpawn( ApplicationBase& game,ModeBase& mode,int spawnfream,int typeenemy )
	:base( game,mode )
{
	spawn_fream = spawnfream;

	Init();
};
AreaEnemySpawn::~AreaEnemySpawn()
{
};

void AreaEnemySpawn::Init()
{
};
bool AreaEnemySpawn::Update( )
{
	return true;
};
bool AreaEnemySpawn::Draw( )
{
	return true;
};
