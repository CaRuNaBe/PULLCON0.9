#include "ActorTitle.h"

ActorTitle::ActorTitle( ApplicationBase& game,int layer,ModeTitle& mode )
	:GameBase( game,layer )
	,_mode( mode )
	,low_movement_pull( 50 )
	,up_movement_pull( 70 )
{
	Initialize();
}

ActorTitle::~ActorTitle()
{}

void ActorTitle::Initialize()
{
	// èÓïÒÇÃèâä˙âª
	_pos = {0,0};
	_size = {0,0};
	_colPos = {0,0};
	_colSize = {0,0};
	_cnt = 0;
	_spd = 0.0f;
}

bool ActorTitle::Update()
{
	_cnt++;
	return true;
}

void ActorTitle::UpdateCollision()
{
	_collision.min = _pos + _colPos;
	_collision.max = _pos + _colPos + _colSize;
}

bool ActorTitle::IsHitObject( ActorTitle& object )
{
	// AABBÇ≈ìñÇΩÇËîªíË
	if ( Intersect( object.GetCollision(),_collision ) )
	{
		return true;
	}
	return false;
}

bool ActorTitle::Draw()
{
	return true;
}

bool ActorTitle::DebugDraw()
{
	DrawCollision();
	return true;
}

void ActorTitle::DrawCollision()
{
#if _DEBUG
	_collision.Draw( rand() % 256,rand() % 256,rand() % 256 );
#endif
}

