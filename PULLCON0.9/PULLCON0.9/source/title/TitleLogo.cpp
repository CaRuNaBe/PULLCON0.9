#include "TitleLogo.h"
#include "Dxlib.h"
TitleLogo::TitleLogo( ApplicationBase& game,int layer,ModeTitle& mode )
	: ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_Logo.png" );

	Initialize();
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Initialize()
{
	ActorTitle::Initialize();

	_pos = {400.0f,100.0f};
	_size.x = 1202.0f;
	_size.y = 300.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 1202.0f;
	_colSize.y = 300.0f;
	_spd = 0;
}

bool TitleLogo::Update()
{
	ActorTitle::Update();
	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitleLogo::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}


