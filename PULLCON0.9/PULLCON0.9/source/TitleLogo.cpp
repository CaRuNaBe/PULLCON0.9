#include "TitleLogo.h"
#include "Dxlib.h"
TitleLogo::TitleLogo()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_Logo.png" );

	Init();
}

TitleLogo::~TitleLogo()
{}

void TitleLogo::Init()
{
	ActorBase2d::Init();

	// プレイヤー情報の初期化
	_pos.x = 400.0f;
	_pos.y = 100.0f;
	_size.x = 1202.0f;
	_size.y = 300.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 1202.0f;
	_colSize.y = 300.0f;
	_spd = 0;

}

bool TitleLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	
	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitleLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}


