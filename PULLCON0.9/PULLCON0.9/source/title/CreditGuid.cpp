#include "CreditGuid.h"
#include "Dxlib.h"
CreditGuid::CreditGuid( ApplicationBase& game,int layer,ModeTitle& mode ): ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_CreditMenuIcon.png" );

	Initialize();
}

CreditGuid::~CreditGuid()
{}

void CreditGuid::Initialize()
{
	ActorTitle::Initialize();

	_pos = {890.0f,800.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
}

bool CreditGuid::Update()
{
	ActorTitle::Update();
	UpdateCollision();	// コリジョン更新
	return true;
}


bool CreditGuid::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	return true;
}
