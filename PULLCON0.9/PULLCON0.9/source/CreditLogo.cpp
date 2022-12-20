#include "CreditLogo.h"
#include "Dxlib.h"
CreditLogo::CreditLogo()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_CreditLogo.png" );

	Init();
}

CreditLogo::~CreditLogo()
{}

void CreditLogo::Init()
{
	ActorBase2d::Init();
	_pos.x = 900.0f;
	_pos.y = 900.0f;
	_size.x = 156.0f;
	_size.y = 466.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 156.0f;
	_colSize.y = 466.0f;
	_spd = 0;
}

bool CreditLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	
	UpdateCollision();	// コリジョン更新
	return true;
}


bool CreditLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}