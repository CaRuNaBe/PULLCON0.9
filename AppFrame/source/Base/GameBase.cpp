#include "GameBase.h"
GameBase::GameBase( ApplicationBase& _game,int _layer )
	: game( _game )
	,layer( _layer )
	,dead( false )
	,isUpdateSkip( false )
	,isDrawSkip( false )
{
}

GameBase::~GameBase()
{
}

