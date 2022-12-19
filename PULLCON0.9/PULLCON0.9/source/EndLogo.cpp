#include "EndLogo.h"
#include "Dxlib.h"
EndLogo::EndLogo()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_EndLogo.png" );

	Init();
}

EndLogo::~EndLogo()
{}

void EndLogo::Init()
{
	ActorBase2d::Init();
	_pos.x = 1350.0f;
	_pos.y = 900.0f;
	_size.x = 156.0f;
	_size.y = 466.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 156.0f;
	_colSize.y = 466.0f;
	_spd = 0;
}

bool EndLogo::Update( ApplicationBase& game )
{
	ActorBase2d::Update( game );
	
	UpdateCollision();	// コリジョン更新
	return true;
}


bool EndLogo::Draw( ApplicationBase& game )
{
	ActorBase2d::Draw( game );
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}