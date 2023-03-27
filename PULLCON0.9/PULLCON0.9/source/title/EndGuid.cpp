#include "EndGuid.h"
#include "Dxlib.h"
EndGuid::EndGuid( ApplicationBase& game,int laysr,ModeTitle& mode ): ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Titlle_EndMenuIcon.png" );

	Initialize();
}

EndGuid::~EndGuid()
{
}

void EndGuid::Initialize()
{
	ActorTitle::Initialize();

	_pos = {1370.0f,800.0f};
	_size = {91.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {91.0f,86.0f};
	_spd = 0;
}

bool EndGuid::Update()
{
	ActorTitle::Update();
	UpdateCollision();	// コリジョン更新
	return true;
}


bool EndGuid::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}
