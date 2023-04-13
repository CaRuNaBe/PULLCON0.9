#include "GameBase.h"
GameBase::GameBase( ApplicationBase& _game,int layer )
	: _game( _game )
	,layer( layer )
	,is_dead( false )
	,is_update_skip( false )
	,is_draw_skip( false )
	,cnt( 0 )
{}

GameBase::~GameBase()
{}

