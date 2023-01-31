#include "ActorBase2d.h"

ActorBase2d::ActorBase2d():base()
{
	Init();
}

ActorBase2d::~ActorBase2d()
{
}

void ActorBase2d::Init()
{
	base::Init();
	// 情報の初期化
	_pos = {0,0};
	_size = {0,0};
	_colPos = {0,0};
	_colSize = {0,0};
	_cnt = 0;
	_spd = 0.0f;
}

bool ActorBase2d::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );
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
	// AABBで当たり判定
	if ( Intersect( object.GetCollision(),_collision ) )
	{
		return true;
	}
	return false;
}

bool ActorBase2d::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	return true;
}

void ActorBase2d::DrawCollision()
{
#if _DEBUG
	_collision.Draw( rand() % 256,rand() % 256,rand() % 256 );
#endif
}

