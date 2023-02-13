#include "GameBase.h"
GameBase::GameBase( ApplicationBase& _game,int _layer )
	: game( _game )
	,layer( _layer )
	,is_dead( false )
	,is_update_skip( false )
	,is_draw_skip( false )
{
}

GameBase::~GameBase()
{
}

