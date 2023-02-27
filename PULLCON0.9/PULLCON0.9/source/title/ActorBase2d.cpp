#include "ActorBase2d.h"

ActorBase2d::ActorBase2d( ApplicationBase& game,ModeTitle& mode )
	:base( game )
	,_mode( mode )
{
	Init();
}

ActorBase2d::~ActorBase2d()
{}

void ActorBase2d::Init()
{
	base::Init();
	// èÓïÒÇÃèâä˙âª
	_pos = {0,0};
	_size = {0,0};
	_colPos = {0,0};
	_colSize = {0,0};
	_cnt = 0;
	_spd = 0.0f;
}

bool ActorBase2d::Update()
{
	base::Update();
	_cnt++;
	return true;
}

void	ActorBase2d::UpdateCollision()
{
	_collision.min = _pos + _colPos;
	_collision.max = _pos + _colPos + _colSize;
}

bool	ActorBase2d::IsHitObject( ActorBase2d& object )
{
	// AABBÇ≈ìñÇΩÇËîªíË
	if ( Intersect( object.GetCollision(),_collision ) )
	{
		return true;
	}
	return false;
}

bool ActorBase2d::Draw()
{
	base::Draw();
	return true;
}

void ActorBase2d::DrawCollision()
{
#if _DEBUG
	_collision.Draw( rand() % 256,rand() % 256,rand() % 256 );
#endif
}

